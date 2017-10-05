#include <a_samp>
#include <list> // http://pastebin.com/zzxLg9qE

public OnFilterScriptInit()
{
	print("\n=============================================");
	print("= Linked lists in PAWN example filterscript =");
	print("=                            Made by BigETI =");
	print("= Loaded!                                   =");
	print("=============================================\n");
	new LIST::init<my_list>, LIST::init<my_list_2>;
	LIST::push_back(my_list, 1337);
	LIST::insert(my_list, LIST::push_back(my_list, 10000), 5);
	LIST::pop_back(my_list);
	LIST::push_back_arr(my_list_2, {1, 2, 3});
	printf("Potential found: 0x%x", _:LIST::insert_arr(my_list, LIST::push_back(my_list, 2), {7, 8, 5, 2, 6}));
	LIST::push_back(my_list_2, 500);
	LIST::erase(my_list, LIST::push_back(my_list, 3));
	LIST::push_back(my_list_2, 7);
	LIST::push_back(my_list, 4);
	LIST::push_back(my_list_2, 1000);
	LIST::push_front(my_list, 10);
	LIST::push_front(my_list, 20);
	LIST::pop_front(my_list);
	LIST::sort(my_list_2);
	printf(" Memory: %d", LIST::get_data_cell_size(my_list));
	printf(" Memory: %d", LIST::get_all_cell_size(my_list));
	LIST::foreach<list_it>(my_list) printf(" Address: 0x%x | Size of: %d | Value: %d", _:list_it, LIST_IT::data_size(list_it), MEM::get_val(LIST_IT::data_ptr(list_it)));
	LIST::foreach_rev<list_it>(my_list_2) printf(" Address: 0x%x | Size of: %d | Value: %d", _:list_it, LIST_IT::data_size(list_it), MEM::get_val(LIST_IT::data_ptr(list_it)));
	printf(" Found: 0x%x, Amount: %d", _:LIST_find_arr(my_list, {7, 8}), LIST_count_found_arr(my_list, {7, 8}));
	LIST::clear(my_list);
	LIST::clear(my_list_2);
	for(new i = 0; i < 5000000; i++) LIST::push_back(my_list, i);
	new a, b;
	a = GetTickCount();
	LIST::foreach<my_iterator>(my_list){}
	b = GetTickCount();
	printf(" Speed: %d ms", b-a);
	a = GetTickCount();
	LIST::foreach<my_iterator>(my_list){}
	b = GetTickCount();
	printf(" Speed: %d ms", b-a);
	a = GetTickCount();
	LIST::foreach<my_iterator>(my_list){}
	b = GetTickCount();
	printf(" Speed: %d ms", b-a);
	LIST::clear(my_list);
	return 1;
}

public OnFilterScriptExit()
{
	print("\n=============================================");
	print("= Linked lists in PAWN example filterscript =");
	print("=                            Made by BigETI =");
	print("= Unloaded!                                 =");
	print("=============================================\n");
	return 1;
}