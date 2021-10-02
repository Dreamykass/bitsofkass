
The simplest and most crude way to do this is the following:

* get `.aar` from <https://mvnrepository.com/artifact/io.objectbox/objectbox-android/2.9.1>
* extract it, check if `/jni/armeabi-v7a/libobjectbox-jni.so` exists
  (different android archs might use `/arm64-v8a/` or whatever)
* add `target_link_libraries(exec_name PRIVATE path/to/libobjectbox-jni.so)`
* copy `libobjectbox-jni.so` to `build-project_name/android-build/libs/armeabi-v7a`
  (where `build-...` is the build directory of the project)
* get `objectbox.h` with the C API from <https://github.com/objectbox/objectbox-c/blob/main/include/objectbox.h> and include it in the project
* add `qDebug() << "objectbox version: " << obx_version_string();` or something
  to test if objectbox gets linked correctly
* enjoy

This cares not about the versioning. In my simple test I had version mismatch, 
where the C API was 0.14, while `obx_version_string` returned 0.12.0 or something.
