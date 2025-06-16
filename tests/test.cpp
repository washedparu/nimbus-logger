#include "nimbus_c_api.h"

int main() {
    nl_setup_logging("log_dir_name");

    NL_LOG(NL_DEBUG_LOG, "This is a debug message.");
    NL_LOG(NL_INFO_LOG, "Hello from C!");
    NL_LOG(NL_WARN_LOG, "This is a warning.");
    NL_LOG(NL_ERROR_LOG, "An error occurred: code %d", 404);
    NL_LOG(NL_CRITICAL_LOG, "Critical issue detected.");
    NL_LOG(NL_FATAL_LOG, "Fatal crash imminent!");

    return 0;
}
