[[nodiscard]] int something() {
    return 1;
}

// this may be useful in code which disable expection.
// the func which returns Status, result cannot be discard.
enum class [[nodiscard]] Status {
    Ok,
    LogicError,
    RuntimeError,
    IoError,
};

Status doRead() {
    return Status::IoError;
}

int main() {
    // doRead(); 将会有一个返回值不可忽略的warning.
    if(Status s = doRead(); s != Status::Ok) {
        //something(); 将会有一个返回值不可被忽略的warning.
        [[maybe_unused]] int a = something();
    }
    return 0;
}