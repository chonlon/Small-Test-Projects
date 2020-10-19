void doSomething() {
    
}

void doSomethingElse() {
    
}


int main(int argc, const char**) {
    switch(argc){
        case 1:
            doSomething();
            //[[fallthrough]];
        case 2:
            doSomethingElse();
    }
}