#include <glog/logging.h>

int main(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, 0);
    google::InitGoogleLogging(argv[0]);
    

    //FLAGS_log_dir = ".";

    LOG(INFO) << "Found " << 3 << " cookies";

    for (int i = 0; i < 10; ++i) {
        LOG_EVERY_N(ERROR, 10) << "Found 1 apple";
    }

    DLOG(WARNING) << "Found 4 peach";

#if 0
    LOG(FATAL) << "Found 1 wine";
#endif

    return 0;
}