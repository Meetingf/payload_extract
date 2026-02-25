#pragma once

#include "minilog.h"

#define LOG_COLOR_RED       ""
#define LOG_COLOR_RED2      ""
#define LOG_COLOR_GREEN     ""
#define LOG_COLOR_GREEN2    ""
#define LOG_COLOR_BROWN     ""
#define LOG_COLOR_BROWN2    ""
#define LOG_COLOR_BLUE      ""
#define LOG_COLOR_BLUE2     ""
#define LOG_COLOR_PURPLE    ""
#define COLOR_NONE          ""

#if defined(LOG_ENABLE_COLOR)
#define LOG_COLOR(COLOR, fmt)        fmt
#define LOG_COLOR_BOLD(COLOR, fmt)   fmt
#else
#define LOG_COLOR(COLOR, fmt) fmt
#define LOG_COLOR_BOLD(COLOR, fmt) fmt
#endif

#define LOG_TAG(tag) minilog::set_log_tag(tag)

#define RED(fmt)              LOG_COLOR(LOG_COLOR_RED, fmt)
#define RED_BOLD(fmt)         LOG_COLOR_BOLD(LOG_COLOR_RED, fmt)
#define RED2(fmt)             LOG_COLOR(LOG_COLOR_RED2, fmt)
#define RED2_BOLD(fmt)        LOG_COLOR_BOLD(LOG_COLOR_RED2, fmt)
#define GREEN2_BOLD(fmt)      LOG_COLOR_BOLD(LOG_COLOR_GREEN2, fmt)
#define BROWN(fmt)            LOG_COLOR(LOG_COLOR_BROWN, fmt)
#define BROWN2(fmt)           LOG_COLOR(LOG_COLOR_BROWN2, fmt)
#define BROWN2_BOLD(fmt)      LOG_COLOR_BOLD(LOG_COLOR_BROWN2, fmt)
#define BROWN_BOLD(fmt)       LOG_COLOR_BOLD(LOG_COLOR_BROWN, fmt)
#define BLUE(fmt)             LOG_COLOR(LOG_COLOR_BLUE, fmt)
#define BLUE_BOLD(fmt)        LOG_COLOR_BOLD(LOG_COLOR_BLUE, fmt)
#define BLUE2_BOLD(fmt)       LOG_COLOR_BOLD(LOG_COLOR_BLUE2, fmt)

#ifdef LOG_DEBUG
#define LOGCD(fmt, ...) minilog::log_debug_tag_color(fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) minilog::log_debug(fmt, ##__VA_ARGS__)
#else
#define LOGCD(fmt, ...)
#define LOGD(fmt, ...)
#endif

#define LOGCV(fmt, ...) minilog::log_verbose_tag_color(fmt, ##__VA_ARGS__)
#define LOGCI(fmt, ...) minilog::log_info_tag_color(fmt, ##__VA_ARGS__)
#define LOGCW(fmt, ...) minilog::log_warn_tag_color(fmt, ##__VA_ARGS__)
#define LOGCE(fmt, ...) minilog::log_error_tag_color(fmt, ##__VA_ARGS__)

#define LOGV(fmt, ...) minilog::log_verbose(fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) minilog::log_info(fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) minilog::log_warn(fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) minilog::log_error(fmt, ##__VA_ARGS__)
