fn main() {
    let manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();

    // Path to your StaticLibrary include directory
    let static_include = format!("{}/../../StaticLibrary/include", manifest_dir);

    // Path to directory containing built RansacLibrary (.lib/.a)
    // You can set RANSAC_LIB_DIR env var from CMake or build scripts.
    let ransac_lib_dir = std::env::var("RANSAC_LIB_DIR").unwrap_or_else(|_| {
        format!("{}/../../build/StaticLibrary/Debug", manifest_dir)
    });

    cxx_build::bridge("src/lib.rs")
        .file(format!("{}/../../StaticLibrary/src/ransac_bridge.cpp", manifest_dir))
        .include(&static_include)
        .include("include")
        .flag_if_supported("-std=c++17")
        .compile("ransac_bridge_cxx");

    println!("cargo:rustc-link-search=native={}", ransac_lib_dir);
    println!("cargo:rustc-link-lib=static=RansacLibrary"); // name of your static lib
    // On MSVC you might need:
    // println!("cargo:rustc-link-lib=dylib=msvcrt"); // rarely needed
}