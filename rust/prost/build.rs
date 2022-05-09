use prost_build::compile_protos;

fn main() {
  compile_protos(&["Person.proto"], &["."]).unwrap();
}
