#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "graph_maker/generator.h"
#include "shortest_path_finder/path.h"

#define EXIT_UNEXPECTED_FAILURE 2

void print_too_many_flags_error(char f)
{
    fprintf(stderr, "Błąd przy wprowadzaniu argumentów!!!\nFlaga \"-%c\" była wprowadzona więcej niż raz!!!\n", f);
}

void print_help()
{
    fprintf(stderr, "\nUruchom program bez argumentów albo z flagą \"-H\", aby uzyskać więcej informacji o argumentach!\n");
}

void print_args_are_invalid()
{
    fprintf(stderr, "Niepoprawne argumenty!!!\n\n");
}

void print_usage();

void print_usage_full();

void print_unexpected_error(char *message)
{
    fprintf(stderr, "Nieoczekiwany błąd!\n");
    fprintf(stderr, "%s", message);
}

int main(int argc, char **argv)
{
    char mode = 'n';
    // generating arguments "-g" flag
    char gen_graf_mode = 'a';            // either "-a" or "-b" or "-c"
    int num_of_rows = 5;                 // "-h [num_of_rows]"
    int num_of_columns = 5;              // "-w [num_of_columns]"
    double lower_bounds_of_weight = 0.0; // "-l [lower_bounds_of_weight]"
    double upper_bounds_of_weight = 1.0; // "-u [upper_bounds_of_weight]"
    int override_mode = 0;               // "-o"
    // pathfinding arguments "-p" flag1
    int extended_answer_mode = 0; // "-e"
    char *nodes = "";
    // shared argument (based on context of use)
    char *filename = "graph_gen.txt"; // "-f [file_name]"

    // flags will check whether the argument were passed more than one time
    int flag_mode_gen = 0;
    int flag_mode_path = 0;
    int flag_gen_graf_mode = 0;
    int flag_rows = 0;
    int flag_columns = 0;
    int flag_lower_bounds = 0;
    int flag_upper_bounds = 0;
    int flag_override_mode = 0;
    int flag_extended_answer_mode = 0;
    int flag_filename = 0;

    // flags for preventing mixing modes and their arguments
    // counters increase when unique (made for one mode only) flags are used
    int count_args_gen = 0;
    int count_args_path = 0;

    int option;
    char *next;
    while ((option = getopt(argc, argv, "gp:abch:w:l:u:oef:H")) != -1)
    {
        switch (option)
        {
        case 'g':
            if (flag_mode_gen)
            {
                print_too_many_flags_error('g');
                print_help();
                return EXIT_FAILURE;
            }
            mode = 'g';
            flag_mode_gen++;
            break;
        case 'p':
            if (flag_mode_path)
            {
                print_too_many_flags_error('p');
                print_help();
                return EXIT_FAILURE;
            }
            mode = 'p';
            nodes = optarg;
            flag_mode_path++;
            break;
        case 'a':
            if (flag_gen_graf_mode)
            {
                print_args_are_invalid();
                fprintf(stderr, "Dozwolone jest wprowadzenie tylko jednej flagi do trybu!!!\n");
                print_help();
                return EXIT_FAILURE;
            }
            gen_graf_mode = 'a';
            flag_gen_graf_mode++;
            break;
        case 'b':
            if (flag_gen_graf_mode)
            {
                print_args_are_invalid();
                fprintf(stderr, "Dozwolone jest wprowadzenie tylko jednej flagi do trybu!!!\n");
                print_help();
                return EXIT_FAILURE;
            }
            gen_graf_mode = 'b';
            flag_gen_graf_mode++;
            break;
        case 'c':
            if (flag_gen_graf_mode)
            {
                print_args_are_invalid();
                fprintf(stderr, "Dozwolone jest wprowadzenie tylko jednej flagi do trybu!!!\n");
                print_help();
                return EXIT_FAILURE;
            }
            gen_graf_mode = 'c';
            flag_gen_graf_mode++;
            break;
        case 'h':
            if (flag_rows)
            {
                print_too_many_flags_error('h');
                print_help();
                return EXIT_FAILURE;
            }
            num_of_rows = strtol(optarg, &next, 10);
            if (*next != '\0')
            {
                print_args_are_invalid();
                fprintf(stderr, "Podana liczba wierszy nie jest liczbą całkowitą!!!\n");
                fprintf(stderr, "Podana wartość: %s\n", optarg);
                print_help();
                return EXIT_FAILURE;
            }
            flag_rows++;
            break;
        case 'w':
            if (flag_columns)
            {
                print_too_many_flags_error('w');
                print_help();
                return EXIT_FAILURE;
            }
            num_of_columns = strtol(optarg, &next, 10);
            if (*next != '\0')
            {
                print_args_are_invalid();
                fprintf(stderr, "Podana liczba kolumn nie jest liczbą całkowitą!!!\n");
                fprintf(stderr, "Podana wartość: %s\n", optarg);
                print_help();
                return EXIT_FAILURE;
            }
            flag_columns++;
            break;
        case 'l':
            if (flag_lower_bounds)
            {
                print_too_many_flags_error('l');
                print_help();
                return EXIT_FAILURE;
            }
            lower_bounds_of_weight = strtod(optarg, &next);
            if (*next != '\0')
            {
                print_args_are_invalid();
                fprintf(stderr, "Podana liczba nie jest liczbą rzeczywistą!!!\n");
                fprintf(stderr, "Podana wartość: %s\n", optarg);
                print_help();
                return EXIT_FAILURE;
            }
            flag_lower_bounds++;
            break;
        case 'u':
            if (flag_upper_bounds)
            {
                print_too_many_flags_error('u');
                print_help();
                return EXIT_FAILURE;
            }
            upper_bounds_of_weight = strtod(optarg, &next);
            if (*next != '\0')
            {
                print_args_are_invalid();
                fprintf(stderr, "Podana liczba nie jest liczbą rzeczywistą!!!\n");
                fprintf(stderr, "Podana wartość: %s\n", optarg);
                print_help();
                return EXIT_FAILURE;
            }
            flag_upper_bounds++;
            break;
        case 'o':
            if (flag_override_mode)
            {
                print_too_many_flags_error('o');
                print_help();
                return EXIT_FAILURE;
            }
            override_mode = 1;
            flag_override_mode++;
            break;
        case 'e':
            if (flag_extended_answer_mode)
            {
                print_too_many_flags_error('e');
                print_help();
                return EXIT_FAILURE;
            }
            extended_answer_mode = 1;
            flag_extended_answer_mode++;
            break;
        case 'f':
            if (flag_filename)
            {
                print_too_many_flags_error('f');
                print_help();
                return EXIT_FAILURE;
            }
            filename = optarg;
            flag_filename++;
            break;
        case 'H':
            print_usage_full();
            return EXIT_SUCCESS;
            break;
        default:
            print_usage();
            return EXIT_FAILURE;
        }
        count_args_gen = flag_mode_gen + flag_gen_graf_mode + flag_rows + flag_columns + flag_lower_bounds + flag_upper_bounds + flag_override_mode; // equals zero only if gen flags weren't used
        count_args_path = flag_mode_path + flag_extended_answer_mode;                                                                                // equals zero only if path flags weren't used
        if (count_args_gen > 0 && count_args_path > 0)
        {
            fprintf(stderr, "Błąd przy wprowadzaniu argumentów!!!\n");
            if (count_args_gen > count_args_path)
            {
                fprintf(stderr, "Przed flagą \"-%c\" (flaga do trybu szukania najkrótszej ścieżki) zostały użyte flagi do trybu generowania grafu!\n", (char)option);
            }
            else if (count_args_gen < count_args_path)
            {
                fprintf(stderr, "Przed flagą \"-%c\" (flaga do trybu generowania grafu) zostały użyte flagi do trybu szukania najkrótszej ścieżki!\n", (char)option);
            }
            fprintf(stderr, "Niedozwolone jest jednoczesne używanie trybów (\"-g\" i \"-p\") oraz wprowadzanie argumentów nieprzeznaczonych dla wybranego trybu!!!\n");
            print_help();
            return EXIT_FAILURE;
        }
    }
    if (optind < argc)
    {
        fprintf(stderr, "Podano za dużo argumentów!!!\n");
        fprintf(stderr, "Nadmiarowe argumenty:\n");
        while (optind < argc)
        {
            fprintf(stderr, "%s ", argv[optind++]);
        }
        fprintf(stderr, "\n");
        print_help();
        return EXIT_FAILURE;
    }

    if (mode == 'g')
    {
        if (lower_bounds_of_weight < 0)
        {
            print_args_are_invalid();
            fprintf(stderr, "Wprowadzony początek zakresu wag = %lf\n", lower_bounds_of_weight);
            fprintf(stderr, "Zakres wag musi być dodatni!\n");
            print_help();
            return EXIT_FAILURE;
        }
        if (upper_bounds_of_weight < 0)
        {
            print_args_are_invalid();
            fprintf(stderr, "Wprowadzony koniec zakresu wag = %lf\n", lower_bounds_of_weight);
            fprintf(stderr, "Zakres wag musi być dodatni!\n");
            print_help();
            return EXIT_FAILURE;
        }
        if (upper_bounds_of_weight < lower_bounds_of_weight)
        {
            print_args_are_invalid();
            fprintf(stderr, "Wprowadzony zakres wag = (%lf,%lf)\n", lower_bounds_of_weight, upper_bounds_of_weight);
            fprintf(stderr, "Początek zakresu wag musi być mniejszy od końca zakresu!\n");
            print_help();
            return EXIT_FAILURE;
        }
        if (num_of_rows <= 0)
        {
            print_args_are_invalid();
            fprintf(stderr, "Wprowadzona ilość wierszy = %d\n", num_of_rows);
            fprintf(stderr, "Ilość wierszy musi być większa od 0!\n");
            print_help();
            return EXIT_FAILURE;
        }
        if (num_of_columns <= 0)
        {
            print_args_are_invalid();
            fprintf(stderr, "Wprowadzona ilość kolumn = %d\n", num_of_columns);
            fprintf(stderr, "Ilość kolumn musi być większa od 0!\n");
            print_help();
            return EXIT_FAILURE;
        }

        if (!check_if_can_be_opened(filename) || override_mode == 1)
        {
            Graph *graph = NULL;
            if (gen_graf_mode == 'a')
            {
                graph = generate_graph_where_all_connections_exist(lower_bounds_of_weight, upper_bounds_of_weight, num_of_rows, num_of_columns);
            }
            else if (gen_graf_mode == 'b')
            {
                graph = generate_graph_randomly_till_its_connected(lower_bounds_of_weight, upper_bounds_of_weight, num_of_rows, num_of_columns);
            }
            else if (gen_graf_mode == 'c')
            {
                graph = generate_graph_randomly(lower_bounds_of_weight, upper_bounds_of_weight, num_of_rows, num_of_columns);
            }
            else
            {
                print_unexpected_error("Nie został wybrany żaden z trybów\n");
                return EXIT_UNEXPECTED_FAILURE;
            }
            if (graph == NULL)
            {
                print_unexpected_error("Nie udało się utworzyć grafu!\n");
                return EXIT_UNEXPECTED_FAILURE;
            }

            int error = graph_to_file(filename, graph);
            free_graph(&graph);
            if (!error) // if converting graph to file was successful
            {
                fprintf(stdout, "Graf został wygenerowany poprawnie do pliku o ścieżce: \"%s\"\n", filename);
                return EXIT_SUCCESS;
            }
            else
            {
                print_unexpected_error("Nie udało się utworzyć pliku z grafem!\n");
                return EXIT_UNEXPECTED_FAILURE;
            }
        }
        else
        {
            fprintf(stderr, "Plik o ścieżce \"%s\" już istnieje!\n", filename);
            fprintf(stderr, "Uruchom z flagą \"-o\" jeżeli chcesz nadpisać plik!\n");
            print_help();
            return EXIT_FAILURE;
        }
    }
    else if (mode == 'p')
    {
        if (check_if_can_be_opened(filename))
        {
            Graph *graph = NULL;
            char line_with_error[LINE_BUFFER_SIZE];
            int error_code_graph = create_graph_from_file(&graph, filename, line_with_error);
            if (graph != NULL)
            {
                char *ptr = nodes;
                Node_pair_input *pair_input = NULL;
                Dijkstra_result *dijkstra_result = NULL;
                Stack *answer_stack = NULL;
                while (*ptr != '\0')
                {
                    pair_input = fill_input_from_string(&ptr);
                    if (pair_input != NULL)
                    {
                        if (pair_input->start < 0)
                        {
                            print_args_are_invalid();
                            fprintf(stderr, "Wierzchołek o nr = %d nie może istnieć!\n", pair_input->start);
                            fprintf(stderr, "Nr wierzchołka musi być wartością większą od 0!\n");
                            print_help();
                            free_graph(&graph);
                            free(pair_input);
                            return EXIT_FAILURE;
                        }
                        if (pair_input->end < 0)
                        {
                            print_args_are_invalid();
                            fprintf(stderr, "Wierzchołek o nr = %d nie może istnieć!\n", pair_input->end);
                            fprintf(stderr, "Nr wierzchołka musi być wartością większą od 0!\n");
                            print_help();
                            free_graph(&graph);
                            free(pair_input);
                            return EXIT_FAILURE;
                        }
                        if (pair_input->start >= graph->dimension)
                        {
                            print_args_are_invalid();
                            fprintf(stderr, "Wierzchołek o nr = %d nie istnieje w grafie z pliku o ścieżce \"%s\"!\n", pair_input->start, filename);
                            fprintf(stderr, "Dla podanego grafu nr wierzchołków to wartości od 0 do %d!", graph->dimension - 1);
                            free_graph(&graph);
                            free(pair_input);
                            return EXIT_FAILURE;
                        }
                        if (pair_input->end >= graph->dimension)
                        {
                            print_args_are_invalid();
                            fprintf(stderr, "Wierzchołek o nr = %d nie istnieje w grafie z pliku o ścieżce \"%s\"!\n", pair_input->end, filename);
                            fprintf(stderr, "Dla podanego grafu nr wierzchołków to wartości od 0 do %d!\n", graph->dimension - 1);
                            free_graph(&graph);
                            free(pair_input);
                            return EXIT_FAILURE;
                        }
                        dijkstra_result = dijkstra(graph, pair_input->start);
                        if (dijkstra_result == NULL)
                        {
                            print_unexpected_error("Nie udało się uzyskać wyniku algorytmu dijsktry!\n");
                            free_graph(&graph);
                            free(pair_input);
                            return EXIT_UNEXPECTED_FAILURE;
                        }
                        answer_stack = fill_stack_from_dijkstra(dijkstra_result, pair_input->end);
                        if (answer_stack == NULL)
                        {
                            fprintf(stderr, "(%d,%d):Nie istnieje droga z wierzchołka o nr %d do wierzchołka o nr %d!\n", pair_input->start, pair_input->end, pair_input->start, pair_input->end);
                        }
                        else if (extended_answer_mode == 1)
                        {
                            print_extended_answer(answer_stack, pair_input->start, pair_input->end);
                        }
                        else if (extended_answer_mode == 0)
                        {
                            print_basic_path(answer_stack, pair_input->start, pair_input->end);
                        }
                        else
                        {
                            print_unexpected_error("Tryb wypisywania wyniku jest inny niż przewidziany: ");
                            fprintf(stderr, "%d\n", extended_answer_mode);
                            free_graph(&graph);
                            free(pair_input);
                            free_dijkstra_result(&dijkstra_result);
                            free_stack(&answer_stack);
                            return EXIT_UNEXPECTED_FAILURE;
                        }
                    }
                    else
                    {
                        print_args_are_invalid();
                        fprintf(stderr, "Wprowadzone wierzchołki są w błędnym formacie!!!\n");
                        fprintf(stderr, "Błąd zaczął się w miejscu: %.4s\n", ptr);
                        free_graph(&graph);
                        return EXIT_FAILURE;
                    }
                    free(pair_input);
                    free_dijkstra_result(&dijkstra_result);
                }
                free_graph(&graph);
            }
            else
            {
                if (error_code_graph == 1)
                {
                    print_unexpected_error("Nie udało się utworzyć pliku z grafem!\n");
                    return EXIT_UNEXPECTED_FAILURE;
                }
                else if (error_code_graph == 2)
                {
                    fprintf(stderr, "Błąd pliku!!!\n");
                    fprintf(stderr, "Format pliku o ścieżce \"%s\" jest błędny!\n", filename);
                    fprintf(stderr, "Błąd wystąpił w linii:\n%s\n", line_with_error);
                    return EXIT_FAILURE;
                }
                else if (error_code_graph == 3)
                {
                    print_unexpected_error("Wystąpił błąd przy wczytywaniu linii z pliku");
                    return EXIT_UNEXPECTED_FAILURE;
                }
                else if (error_code_graph == 4)
                {
                    fprintf(stderr, "Błąd pliku!!!\n");
                    fprintf(stderr, "Plik o ścieżce \"%s\" jest pusty!\n", filename);
                    return EXIT_FAILURE;
                }
                else if (error_code_graph == 5)
                {
                    fprintf(stderr, "Błąd pliku!!!\n");
                    fprintf(stderr, "Nie może istnieć taki wierzchołek!!!\n");
                    fprintf(stderr, "Indeksy podanych wierzchołków muszą być mniejsze od ich ilości (ilość_wierszy*ilość_kolumn)\n");
                    fprintf(stderr, "Błąd wystąpił w linii:\n%s\n", line_with_error);
                    return EXIT_FAILURE;
                }
                else if (error_code_graph == 6)
                {
                    fprintf(stderr, "Błąd pliku!!!\n");
                    fprintf(stderr, "Możliwe jest tylko połączenie z sąsiednim wierzchołkiem!!!");
                    fprintf(stderr, "Błąd wystąpił w linii:\n%s\n", line_with_error);
                    return EXIT_FAILURE;
                }
                else if (error_code_graph == 7)
                {
                    fprintf(stderr, "Błąd pliku!!!\n");
                    fprintf(stderr, "Wagi muszą być liczbami nieujemnymi!!!\n");
                    fprintf(stderr, "Błąd wystąpił w linii:\n%s\n", line_with_error);
                    return EXIT_FAILURE;
                }
                else
                {
                    print_unexpected_error("Zwrócony kod grafu przy wypełnianiu grafu z pliku jest nieznany!\n");
                    return EXIT_UNEXPECTED_FAILURE;
                }
                print_unexpected_error("");
                return EXIT_FAILURE;
            }
        }
        else
        {
            fprintf(stderr, "Plik o ścieżce \"%s\" nie istnieje!\n", filename);
            print_help();
            return EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "Nie wybrano trybu programu!\n");
        print_usage();
        return EXIT_FAILURE;
    }
    return 0;
}

void print_usage()
{
    fprintf(stderr,
            "\n"
            "                                           Sposób użycia programu w zależności od trybu:\n"
            "\n"
            "***********************************************************************************************************************************************\n"
            "********                                               TRYB GENEROWANIA GRAFU                                                          ********\n"
            "***********************************************************************************************************************************************\n"
            "\n"
            "Użycie: ./graphJD [-g] [-a|-b|-c] [-f nazwa_pliku] [-h liczba_wierszy] [-w liczba_kolumn] [-l dolna_granica_wag] [-u górna_granica_wag] [-o]\n"
            "\n"
            "***********************************************************************************************************************************************\n"
            "********                                          TRYB SZUKANIA NAJKRÓTSZEJ ŚCIEŻKI                                                    ********\n"
            "***********************************************************************************************************************************************\n"
            "\n"
            "Użycie: ./graphJD [-p para_1,...] [-f nazwa_pliku] [-e]\n"
            "\n"
            "Uruchom program z flagą \"-H\", aby uzyskać dokładne informacje o parametrach!\n"
            "\n");
}

void print_usage_full()
{
    fprintf(stderr,
            "\n"
            "                                           Sposób użycia programu w zależności od trybu:\n"
            "\n"
            "***********************************************************************************************************************************************\n"
            "********                                               TRYB GENEROWANIA GRAFU                                                          ********\n"
            "***********************************************************************************************************************************************\n"
            "\n"
            "\n"
            "Użycie: ./graphJD [-g] [-a|-b|-c] [-f nazwa_pliku] [-h liczba_wierszy] [-w liczba_kolumn] [-l dolna_granica_wag] [-u górna_granica_wag] [-o]\n"
            "\n"
            "\n"
            "Argumenty wymagane:\n"
            "-g                                 ustawia tryb działania programu na generowanie grafu na kartce w kratkę\n"
            "                                   domyślnie generowany graf jest spójny z wszystkimi możliwymi krawędziami\n"
            "\n"
            "\n"
            "Argumenty opcjonalne:\n"
            "-a                                 ustawia tryb generowania grafu na generowanie grafu spójnego\n"
            "\n"
            "-b                                 ustawia tryb generowania grafu na losowanie istnienia krawędzi między\n"
            "                                   wierzchołkami grafu aż do momentu utworzenia grafu spójnego\n"
            "\n"
            "-c                                 ustawia tryb generowania grafu na losowanie istnienia krawędzi między\n"
            "                                   wierzchołkami grafu,powstały graf nie musi być spójny\n"
            "\n"
            "-f                                 daje możliwość podania nazwy pliku (nazwa_pliku) ,w którym zapisujemy graf\n"
            "                                   domyślnie nazwa pliku to \"graph_gen.txt\"\n"
            "\n"
            "-h                                 daje możliwość podania jaką liczbe wierszy (liczba_wierszy) generowanego grafu\n"
            "\n"
            "                                   domyśnie liczba wierszy to 5\n"
            "\n"
            "                                   warunki dla zmiennej: zmienna liczba_wierszy jest liczbą całkowitą i liczba_wierszy>0\n"
            "\n"
            "-w                                 daje możliwość podania jaką liczbe kolumn (liczba_kolumn) generowanego grafu\n"
            "\n"
            "                                   domyśnie liczba wierszy to 5\n"
            "\n"
            "                                   warunki dla zmiennej: zmienna liczba_kolumn jest liczbą całkowitą i liczba_kolumn>0\n"
            "\n"
            "-l                                 daje możliwość podania dolnej granicy wartości losowanych wag przejść (dolna_granica_wag) \n"
            "                                   między wierzchołkami generowanego grafu\n"
            "\n"
            "                                   domyśnie dolna granica wartości losowanych wag przejść to 0\n"
            "\n"
            "                                   warunki dla zmiennej: dolna_granica_wag jest liczbą rzeczywistą i dolna_granica_wag>0\n"
            "\n"
            "-u                                 daje możliwość podania górnej granicy wartości losowanych wag przejść (górna_granica_wag)\n"
            "                                   między wierzchołkami generowanego grafu\n"
            "\n"
            "                                   domyśnie dolna granica wartości losowanych wag przejść to 0\n"
            "\n"
            "                                   warunki dla zmiennej: górna_granica_wag jest liczbą rzeczywistą i górna_granica_wag>0\n"
            "\n"
            "-o                                 daje możliwość nadpisania pliku do którego zapisujemy wygenerowany graf jeśli\n"
            "                                   plik o takiej nazwie już istnieje"
            "\n"
            "\n"
            "***********************************************************************************************************************************************\n"
            "********                                           TRYB SZUKANIA NAJKRÓTSZEJ ŚCIEŻKI                                                   ********\n"
            "***********************************************************************************************************************************************\n"
            "\n"
            "\n"
            "Użycie: ./graphJD [-p para_1,...] [-f nazwa_pliku] [-e]\n"
            "\n"
            "\n"
            "Argumenty wymagane:\n"
            "-p                                 ustawia tryb działania programu na odszukiwanie najkrótszej ścieżki między parą ( para_1 )\n"
            "                                   wierzchołków grafu\n"
            "\n"
            "                                   użytkownik może podać jedną parę wierzchołków w formacie\n"
            "                                   a-b gdzie a,b to numery wierzchołków grafu\n"
            "                                   lub\n"
            "                                   użytkownik może podać więcej niż jedną parę w wierzchołków w formacie\n"
            "                                   a-b,c-d,e-f .... gdzie a,b,c,d,e,f to numery wierzchołków grafu\n"
            "\n"
            "                                   warunki dla zmiennych: numery wierzchołków muszą być liczbami całkowitymi większymi od 0\n"
            "\n"
            "\n"
            "Argumenty opcjonalne:\n"
            "-f                                 daje możliwość podania nazwy pliku (nazwa_pliku) z grafem ,w którym program wyszuka\n"
            "                                   najkrótsze ścieżki\n"
            "\n"
            "                                   domyślnie nazwa pliku to \"graph_gen.txt\"\n"
            "\n"
            "-e                                 ustawia tryb wypisywania najkrótszej ścieżki między wierzchołkami na rozszerzony\n"
            "\n"
            "                                  domyślnie tryb wypisywania jest ustawiony na standardowy\n"
            "\n");
}