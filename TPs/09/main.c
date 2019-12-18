// Checks if case range used in note_to_grade function is supported by the compiler
#if (defined(__GNUC__) ||defined(__GNUG__) || defined(__clang__))
    #define HAS_GNU_CLANG
#endif

#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
    #define HAS_MSVC_OR_INTEL
#endif

#if (defined(HAS_GNU_CLANG) && !defined(HAS_MSVC_OR_INTEL))
    #define CASE_RANGE_SUPPORT
#endif
// Error if not
#ifndef CASE_RANGE_SUPPORT
    #error "Your compiler does not support ranges in switch-case statements. Use GCC or Clang"
#endif

// C standard library headers
#include <stdio.h>
#include <stdlib.h>
// Internal Headers
#include "students.h"

int main()
{   
    Student_DL *list = NULL;

    list = add_student(list, "Batuhan", "Ceylan");
    list = add_student(list, "Kaan",    "Kırbıyık");
    list = add_student(list, "Berktan", "Ceylan");
    means_with_threshold(list, 0);
    
    return 0;
}
