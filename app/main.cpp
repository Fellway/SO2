#include <strsafe.h>
#include "../Variables.h"
#include "headers/Monitor.h"
#include "headers/Writer.h"


using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 5 && strcmp(argv[4], READER_PROCESS_NAME) == 0) {
        Monitor monitor(argv);
        monitor.init();
    } else {
        Writer writer(argv);
        writer.init(argv);
    }
}
