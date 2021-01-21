#include <iostream>
#include "vm/vm.hpp"

int main()
{
    //spawn console
    AllocConsole();
    FILE* in;
    FILE* out;

    freopen_s(&in, "conin$", "r", stdin);
    freopen_s(&out, "conout$", "w", stdout);
    freopen_s(&out, "conout$", "w", stderr);

    //create the VM
    JavaVM* jvm;
    JNIEnv* env = vm::create_vm(&jvm, "natives/");
    if (env == NULL) {
        printf("Failed to create JVM! \n");
        return 1;
    }

    //start the program
    jclass start_class = env->FindClass("Start");

    if (start_class)
    {
        jmethodID main_method = env->GetStaticMethodID(start_class, "main", "([Ljava/lang/String;)V");

        if (main_method)
        {
            env->CallStaticVoidMethod(start_class, main_method, NULL);
        }
        else
        {
            printf("Couldn't find main method! \n");
        }
    }
    else
    {
        printf("Couldn't find Start class \n");
    }

    return 0;
}
