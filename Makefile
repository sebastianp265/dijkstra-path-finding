CC:=gcc
CFLAGS:=-g -Wall -Werror -Wfloat-equal

MAKERDIR:=graph_maker/
FINDERDIR:=shortest_path_finder/

DIR_TEST:=test_src/

MAKERDIR_TEST:=test_src/test_graph_maker/
FINDERDIR_TEST:=test_src/test_shortest_path_finder/

MAKEROBJS:= $(MAKERDIR)generator.o $(MAKERDIR)graph.o $(MAKERDIR)queue.o
MAKERHEADERS:= $(MAKERDIR)generator.h $(MAKERDIR)graph.h $(MAKERDIR)queue.h

FINDEROBJS:= $(FINDERDIR)path.o $(FINDERDIR)priority_queue.o $(FINDERDIR)stack.o
FINDERHEADERS:= $(FINDERDIR)path.h $(FINDERDIR)priority_queue.h $(FINDERDIR)stack.h 

MAKER:= $(MAKEROBJS) $(MAKERHEADERS)
FINDER:= $(FINDEROBJS) $(FINDERHEADERS)

MAKEROBJS_TEST:= $(MAKERDIR_TEST)generator_test.o $(MAKERDIR_TEST)graph_test.o $(MAKERDIR_TEST)queue_test.o 
MAKERHEADERS_TEST:= $(MAKERDIR_TEST)generator_test.h $(MAKERDIR_TEST)graph_test.h $(MAKERDIR_TEST)queue_test.h 

FINDEROBJS_TEST:= $(FINDERDIR_TEST)path_test.o $(FINDERDIR_TEST)priority_queue_test.o $(FINDERDIR_TEST)stack_test.o
FINDERHEADERS_TEST:= $(FINDERDIR_TEST)path_test.h $(FINDERDIR_TEST)priority_queue_test.h $(FINDERDIR_TEST)stack_test.h

MAKER_TEST:= $(MAKEROBJS_TEST) $(MAKERHEADERS_TEST)
FINDER_TEST:= $(FINDEROBJS_TEST) $(FINDERHEADERS_TEST)
#$@-name of the target
#$<-first dependency
#$^-all dependencies

graphJD: main.c $(MAKER) $(FINDER)
	$(CC) -o $@ $(CFLAGS) main.c $(MAKEROBJS) $(FINDEROBJS)

test: main_test.c $(MAKER) $(FINDER) $(MAKER_TEST) $(FINDER_TEST) $(DIR_TEST)print_tests.h $(DIR_TEST)print_tests.o
	$(CC) -o $@ $(CFLAGS) main_test.c $(MAKEROBJS) $(FINDEROBJS) $(MAKEROBJS_TEST) $(FINDEROBJS_TEST) $(DIR_TEST)print_tests.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(MAKERDIR)*.o $(FINDERDIR)*.o $(MAKERDIR_TEST)*.o $(FINDERDIR_TEST)*.o $(DIR_TEST)print_tests.o graphJD test