#include "pipeline.h"
#include <stdio.h>
#include <assert.h>

extern void BroadcastRTP(int track_id, void *data, int size);

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
    (void)bus;
    GMainLoop *loop = (GMainLoop *)data;

    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_EOS:
        (void)g_print("End of stream\n");
        (void)g_main_loop_quit(loop);
        break;

    case GST_MESSAGE_ERROR: {
        gchar *debug;
        GError *error;
        (void)gst_message_parse_error(msg, &error, &debug);
        (void)g_free(debug);
        (void)g_printerr("Error: %s\n", error->message);
        (void)g_error_free(error);
        (void)g_main_loop_quit(loop);
        break;
    }

    default:
        break;
    }

    return TRUE;
}

static GstFlowReturn new_sample(GstElement *sink, void *data) {
    GstSample *sample = NULL;
    GstBuffer *buffer = NULL;
    GstMapInfo map;
    (void)g_signal_emit_by_name(sink, "pull-sample", &sample);

    if (!sample) {
        return GST_FLOW_ERROR;
    }

    buffer = gst_sample_get_buffer(sample);
    (void)gst_buffer_map(buffer, &map, GST_MAP_READ);
    (void)BroadcastRTP((int)(uintptr_t)data, map.data, map.size);
    (void)gst_buffer_unmap(buffer, &map);
    (void)gst_sample_unref(sample);
    return GST_FLOW_OK;
}

#define AUDIO_PIPELINE(APPSRC, APPSINK)                                        \
  "appsrc name=" #APPSRC " is-live=true do-timestamp=true format=time ! "      \
  "audio/x-raw, format=S16LE, rate=65536, channels=2, layout=interleaved ! "   \
  "audioconvert ! audioresample ! "                                            \
  "audio/x-raw, format=S16LE, rate=48000, channels=2, layout=interleaved ! "   \
  "opusenc ! rtpopuspay ! appsink name=" #APPSINK " emit-signals=true"

#define VIDEO_PIPELINE(APPSRC, APPSINK)                                        \
  "appsrc name=" #APPSRC " is-live=true do-timestamp=true format=time ! "      \
  "video/x-raw, format=GRAY8, width=160, height=144, framerate=64/1 ! "        \
  "videoconvert ! x264enc speed-preset=ultrafast tune=zerolatency ! "          \
  "video/x-h264, profile=constrained-baseline ! "                              \
  "rtph264pay ! appsink name=" #APPSINK " emit-signals=true"

struct pipeline {
    char *appsrc_name;
    char *appsink_name;
    char *pipeline_string;
    GstElement *appsrc;
    GstElement *appsink;
    GstElement *pipeline;
    GMainLoop *loop;
    GstBus *bus;
};

static struct pipeline pipelines[4] = {
    {
        .appsrc_name = "appsrc0",
        .appsink_name = "appsink0",
        .pipeline_string = AUDIO_PIPELINE(appsrc0, appsink0)
    },
    {
        .appsrc_name = "appsrc1",
        .appsink_name = "appsink1",
        .pipeline_string = VIDEO_PIPELINE(appsrc1, appsink1)
    },
    {
        .appsrc_name = "appsrc2",
        .appsink_name = "appsink2",
        .pipeline_string = AUDIO_PIPELINE(appsrc2, appsink2)
    },
    {
        .appsrc_name = "appsrc3",
        .appsink_name = "appsink3",
        .pipeline_string = VIDEO_PIPELINE(appsrc3, appsink3)
    },
};

int pipeline_write(int id, uint8_t *data, uint32_t size) {
    GstElement *appsrc;
    appsrc = pipelines[id].appsrc;
    GstBuffer *buf = gst_buffer_new_allocate(NULL, size, NULL);
    (void)gst_buffer_fill(buf, 0, data, size);
    (void)gst_app_src_push_buffer(GST_APP_SRC(appsrc), buf);
    return 1;
}

int pipeline_open(int id) {
    GError *error = NULL;
    struct pipeline *p = NULL;
    static int once;

    if (!once++) {
        gst_init(NULL, NULL);
    }

    p = &(pipelines[id]);
    p->pipeline = gst_parse_launch(p->pipeline_string, &error);
    if (error != NULL) {
        (void)fprintf(stderr, "domain: %u code: %d message: %s\n",
            error->domain, error->code, error->message);
        exit(1);
    }
    p->appsrc = gst_bin_get_by_name(GST_BIN(p->pipeline), p->appsrc_name);
    assert(p->appsrc != NULL);
    p->appsink = gst_bin_get_by_name(GST_BIN(p->pipeline), p->appsink_name);
    assert(p->appsink != NULL);
    (void)g_signal_connect(p->appsink, "new-sample", G_CALLBACK(new_sample),
                           (void *)(uintptr_t)id);
    p->bus = gst_pipeline_get_bus(GST_PIPELINE(p->pipeline));
    assert(p->bus != NULL);
    p->loop = g_main_loop_new(NULL, FALSE);
    (void)gst_bus_add_watch(p->bus, bus_call, p->loop);
    (void)gst_element_set_state(p->pipeline, GST_STATE_PLAYING);
    return 1;
}

int pipeline_close(int id) {
    struct pipeline *p;
    p = &(pipelines[id]);

    if (p->appsrc) {
        (void)gst_app_src_end_of_stream(GST_APP_SRC(p->appsrc));
        p->appsrc = NULL;
    }

    if (p->bus) {
        (void)gst_bus_timed_pop_filtered(p->bus, GST_CLOCK_TIME_NONE,
                                         GST_MESSAGE_EOS);
        (void)gst_object_unref(p->bus);
        p->bus = NULL;
    }

    if (p->pipeline) {
        (void)gst_element_set_state(GST_ELEMENT(p->pipeline), GST_STATE_NULL);
        (void)gst_object_unref(p->pipeline);
        p->pipeline = NULL;
    }

    return 1;
}
