#include <stddef.h>
#include "read.h"
#include "bst.h"

int main() {
    Tree forests = NULL;
    program(&forests);
    removeAll(forests);
    return 0;
}

