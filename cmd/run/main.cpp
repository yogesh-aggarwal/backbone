#include <iostream>

#include <backbone/lib/buffer/basic.tcc>

int
main() {
   BasicBuffer<uint8_t, 10> buf('a');

   // FILL
   for (int i = 0; i < 3; i++) {
      auto _ = buf.Write(i + 'a');
   }

   // READ
   for (int i = 0; i < 3; i++) {
      auto result = buf.Read();
      if (!result) {
         result.error->Print();
      } else {
         std::cout << "Value: " << result.value << std::endl;
      }
   }

   return 0;
}
