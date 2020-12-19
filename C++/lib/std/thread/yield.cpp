  #include <iostream>
  #include <chrono>
  #include <thread>
  

  void little_sleep(std::chrono::microseconds us)
  {
      auto start = std::chrono::high_resolution_clock::now();
      auto end = start + us;
      do {
          std::cout << "waiting\n"; 
          std::this_thread::yield(); //////yield, 操作系统切换到其它线程, 这样的话cpu占用率可以低很多
      } while (std::chrono::high_resolution_clock::now() < end);
  }
   
  int main()
  {
      auto start = std::chrono::high_resolution_clock::now();
   
      little_sleep(std::chrono::microseconds(1000));
   
      auto elapsed = std::chrono::high_resolution_clock::now() - start;
      std::cout << "waited for "
                << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
                << " microseconds\n";
  }