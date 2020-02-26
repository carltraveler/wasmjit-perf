#include <eosio/vm/backend.hpp>
#include <eosio/vm/error_codes.hpp>
#include <eosio/vm/host_function.hpp>
#include <eosio/vm/watchdog.hpp>

#include <iostream>
#include <ctime>

using namespace eosio;
using namespace eosio::vm;

namespace eosio { namespace vm {

   template <>
   struct wasm_type_converter<const char*> : linear_memory_access {
      const char* from_wasm(const void* val) { validate_c_str(val); return static_cast<const char*>(val); }
   };

}}


struct example_host_methods {
	void ontio_debug(uint32_t ptr, uint32_t len) {
		std::cout<< "for test ontio_debug"<< len <<"\n";
	}

	void ontio_panic(uint32_t ptr, uint32_t len) {
		std::cout<< "for test ontio_panic" << len <<"\n";
	}
};



/**
 * Simple implementation of an interpreter using eos-vm.
 */
int main(int argc, char** argv) {
   // Thread specific `allocator` used for wasm linear memory.
   wasm_allocator wa;
   // Specific the backend with no "host" for host functions.
   using backend_t = eosio::vm::backend<example_host_methods, eosio::vm::jit>;
   //using backend_t = eosio::vm::backend<eosio::vm::jit>;

   if (argc < 2) {
      std::cerr << "Error, no wasm file provided\n";
      return -1;
   }

   //watchdog wd{std::chrono::seconds(1000)};

   try {
	   using rhf_t     = eosio::vm::registered_host_functions<example_host_methods>;
	   rhf_t::add<example_host_methods, &example_host_methods::ontio_debug, wasm_allocator>("env", "ontio_debug");
	   rhf_t::add<example_host_methods, &example_host_methods::ontio_panic, wasm_allocator>("env", "ontio_panic");

      // Read the wasm into memory.
      auto code = backend_t::read_wasm( argv[1] );

	  clock_t startTime, endTime;

	  startTime = clock();
      // Instaniate a new backend using the wasm provided.
      backend_t bkend( code , rhf_t{});
	  endTime = clock();
	  std::cout << "eosvm compile time:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";

      // Point the backend to the allocator you want it to use.
      bkend.set_wasm_allocator( &wa );

      // Execute any exported functions provided by the wasm.
      bkend.initialize();

      example_host_methods ehm;
      //bkend.execute_all(wd);
      //bkend.execute_all(null_watchdog());
	  startTime = clock();
      bkend(&ehm, "env", "invoke");
	  endTime = clock();
	  std::cout << "eosvm Execute time is:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";
   } catch ( const eosio::vm::exception& ex ) {
      std::cerr << "eos-vm interpreter error\n";
      std::cerr << ex.what() << " : " << ex.detail() << "\n";
   }
   return 0;
}
