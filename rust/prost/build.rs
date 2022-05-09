use prost_build::Config;

fn main() {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=Person.proto");

    Config::new()
        .out_dir("src/proto")
        .compile_protos(&["Person.proto"], &["."])
        .unwrap();
}
