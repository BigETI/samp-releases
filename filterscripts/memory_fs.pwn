#include <a_samp>
#include <memory> // http://pastebin.com/4A8qLB5Z

MEM::struct TEST_STRUCT
{
	TEST_1,
	TEST_2,
	TEST_3,
	TEST_4
}

public OnFilterScriptInit()
{
	print("\n==========================================");
	print("= Memory access plugin test filterscript =");
	print("=                         Made by BigETI =");
	print("= Loaded!                                =");
	print("==========================================\n");
	
	// Get AMX pointer
	printf("AMX pointer: 0x%x", _:MEM::amx_ptr());
	
	// Allocate memory
	new Pointer:foo = MEM_malloc(TEST_STRUCT);

	//If failed
	if(_:foo == NULL)
	{
		print("Failed to allocate memory for \"foo\" pointer.");
		return 1;
	}
	
	// Print the pointer of the allocated memory
	printf("Allocated memory is located at 0x%x", _:foo);

	// Set values using pointers as destination
	MEM::set_val(foo, TEST_1, 10);
	MEM::set_val(foo, TEST_2, 9);
	MEM::set_val(foo, TEST_3, 8);
	MEM::set_val(foo, TEST_4, 7);

	// Print the values by getting values from pointers
	printf("MEM_EX::get_val(foo->TEST_1) = %d | MEM_EX::get_val(foo->TEST_2) = %d | MEM_EX::get_val(foo->TEST_3) = %d | MEM_EX::get_val(foo->TEST_4) = %d", MEM_EX::get_val(foo->TEST_1), MEM_EX::get_val(foo->TEST_2), MEM_EX::get_val(foo->TEST_3), MEM_EX::get_val(foo->TEST_4));
	
	// Print the memory results
	MEM_EX::foreach(TEST_STRUCT, foo_i)
	{
	    printf("MEM_EX::foreach test: ( address = 0x%x | value = %d )", _:MEM_EX::get_ptr(foo->foo_i), MEM_EX::get_val(foo->foo_i));
	}
	
	// Sort the memory
	MEM::sort(foo, _, TEST_STRUCT);
	
	// Print the memory results
	MEM_EX::foreach(TEST_STRUCT, foo_i)
	{
	    printf("MEM_EX::foreach test: ( address = 0x%x | value = %d )", _:MEM_EX::get_ptr(foo->foo_i), MEM_EX::get_val(foo->foo_i));
	}
	
	//Sort the memory by reversed order
	MEM::sort(foo, _, TEST_STRUCT, MEM_ENUM::sort_reverse);
	
	// Print the memory results
	MEM_EX::foreach(TEST_STRUCT, foo_it)
	{
	    printf("MEM_EX::foreach test: ( address = 0x%x | value = %d )", _:MEM_EX::get_ptr(foo->foo_it), MEM_EX::get_val(foo->foo_it));
	}
	
	// Mix the memory
	MEM::mix(foo, _, TEST_STRUCT);

	// Print the memory results
	MEM_EX::foreach(TEST_STRUCT, foo_it)
	{
	    printf("MEM_EX::foreach test: ( address = 0x%x | value = %d )", _:MEM_EX::get_ptr(foo->foo_it), MEM_EX::get_val(foo->foo_it));
	}

	// Free memory (IMPORTANT!)
	MEM::free(foo);
	
	// Get variable address and value by address
	new test_var = 1337;
	printf("\"test_var\" address: 0x%x | \"test_var\" value by address: %d", _:MEM::get_addr(test_var), MEM::get_val(MEM::get_addr(test_var)));
	return 1;
}

public OnFilterScriptExit()
{
	print("\n==========================================");
	print("= Memory access plugin test filterscript =");
	print("=                         Made by BigETI =");
	print("= Unloaded!                              =");
	print("==========================================\n");
	return 1;
}