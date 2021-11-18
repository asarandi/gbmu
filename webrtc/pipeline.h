#ifndef PIPELINE_H
# define PIPELINE_H

#include <glib.h>
#include <gst/app/gstappsrc.h>
#include <gst/gst.h>
#include <stdint.h>

int pipeline_write(int id, uint8_t *data, uint32_t size);
int pipeline_open(int id);
int pipeline_close(int id);

#endif
