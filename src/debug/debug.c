/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 14:52:20 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void	ft_deb_here_doc(t_ms *ms)
// {
// 	setbuf(stdout, 0);
// 	ms->global_flags = 1;
// 	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
// 	ms->cmds->next = NULL;
// 	ms->cmds->cmd->redir->next->next->next = NULL;
// 	ms->cmds->cmd->redir->target = NULL;
// 	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
// 	ms->cmds->cmd->flags = 1;
// 	ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
// 	ms->cmds->cmd->redir->instruction = redir_here_doc;
// 	ms->cmds->cmd->redir->hd_del = ft_strdup("eof");
// 	ms->cmds->cmd->redir->next->target = NULL;
// 	ms->cmds->cmd->redir->next->next->target = NULL;
// 	ms->cmds->cmd->redir->next->instruction = redir_here_doc;
// 	ms->cmds->cmd->redir->next->next->instruction = redir_here_doc;
// 	ms->cmds->cmd->redir->next->hd_del = ft_strdup("eof");
// 	ms->cmds->cmd->redir->next->next->hd_del = ft_strdup("eof");
// 	ms->cmds->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
// 	ms->cmds->cmd->redir->next->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
// }

void	ft_deb_commands(t_ms *ms)
{
	int case_nb;

	case_nb = INT_MIN;
	// setbuf(stdout, 0);

	ft_printf("Debugging command execution\n");
	ft_printf("Debug cases need to be finalized and doublechecked\n");
	ft_printf("0 - cat ./valgrind_line.txt // Working properly\n");
	ft_printf("1 - ls -l | cat -e // Working properly\n");
	ft_printf("2 - ls -l > file1 | cat -e > file2 // Working properly\n");
	ft_printf("3 - ls -l > file1 | cat -e > file2 | wc -l > file3 // Working properly\n");
	ft_printf("4 - cat | cat | ls\n // Working properly i think\n");
	ft_printf("5 - echo hello world | grep hello > output.txt // echo not yet implemented (working with echo executable)\n");
	ft_printf("6 - cat < input.txt | sort | uniq // working properly\n"); // [ ] leaks if input.txt does not exist
	ft_printf("7 - find . -type f | xargs grep TODO > todo_list.txt // Working properly\n");
	ft_printf("8 - mkdir new_folder | ls -l // Working properly\n");
	ft_printf("9 - tar -czf archive.tar.gz /new_folder | ls -l archive.tar.gz // Working properly\n");
	ft_printf("10 - echo $HOME > home_directory.txt // echo not yet implemented!! (Variable transfer to execve also missing)\n"); // [ ] Variable transfer to execve also missing!!
	ft_printf("11 - ps aux | grep bash | wc -l // Working properly\n");
	ft_printf("12 - cd /tmp | touch temp_file | ls -l temp_file // cd not yet implemented\n"); // [ ] cd not yet implemented
	ft_printf("13 - Test with cat command without further input // working properly\n");
	ft_printf("14 - three fantasy commands to see behavior and error messages. It is a pipeline with 3 commands. // Error Messages printed properly, leaking like crazy!!\n"); // [ ] Error Messages printed properly, leaking like crazy!!
	ft_printf("15 - \"make -j re\"\n");	// [ ]
	ft_printf("16 - \"make -j exv\"\n"); 	// [ ]
	ft_printf("17 - \"make -j fclean\"\n"); 	// [ ]
	ft_printf("18 - starting minishell in minishell\n"); // [ ]
	ft_printf("19 - clear\n");
	ft_printf("20 - case number 20 for \"<<eof cat | cat >hd_output1\" // working properly\n");
	ft_printf("21 - sjlfkdsjfs | cat | ls\n"); // [ ]
	ft_printf("22 - cat | sjlfkdsjfs | ls\n"); // [ ]
	ft_printf("23 - nc -l 80\n"); // [ ]
	ft_printf("24 - print current stabs\n"); // [ ]
	ft_printf("25 - case to add a new variable to the local stab\n"); // [ ]
	ft_printf("26 - case to make local variable global\n"); // [ ]
	ft_printf("27 - add a new global variable\n");
	ft_printf("28 - add 20 new global variables\n");
	ft_printf("29 - remove a global variable\n");
	ft_printf("30 - change a global variable\n");
	ft_printf("31 - change a local variable\n");
	ft_printf("32 - case to update a val at runtime\n");
	ft_printf("33 - case to recall a val from stab\n");
	ft_printf("34 - case to recall a nonexistent val from stab\n");
	ft_printf("35 - Test with echo klsjhdsdf klsjhdsdf klsjhdsdf > home_directory.txt\n");
	ft_printf("36 - Test with echo klsjhdsdf klsjhdsdf klsjhdsdf\n");
	ft_printf("37 - Test with pwd klsjhdsdf klsjhdsdf klsjhdsdf\n");
	ft_printf("38 - Test with pwd without any further arguments\n");
	ft_printf("39 - Test with cd ..\n");
	ft_printf("40 - export\n");
	ft_printf("41 - export new=bla\n");
	ft_printf("42 - export new2\n");
	ft_printf("43 - export new=bla\n");
	ft_printf("44 - export TEST1=20000 TEST2=30000 TEST3\n");
	ft_printf("45 - export empty=\"\"\n");
	ft_printf("46 - unset non existent var \"NONEXISTENT\"\n");
	ft_printf("47 - unset NEW1 NEW2 NEW3 (execute debug case 28 before)\n");
	ft_printf("48 - env with no arguments\n");
	ft_printf("49 - env NEW1 NEW2 NEW3 should return error\n");

	case_nb = ft_atoi(readline("Choose debug case: "));
	while (case_nb < 0 || case_nb > 49)
	{
		ft_printf("Error: wrong selection\n");
		case_nb = ft_atoi(readline("Choose debug case: "));
	}
	if (case_nb == 0)
	{
		ft_printf("Test with cat command and single input argument file\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("./valgrind_line.txt");
		ms->cmds->cmd->words->next->next = NULL;
		ms->be->nb_cmds = 1;
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 1)
	{
		ft_printf("Test with ls -l | cat -e\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("ls");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->cmd->flags = 0;
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 2)
	{
		ft_printf("Test with ls -l > file1 | cat -e > file2\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("ls");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->next->instruction = redir_outfile;
		ms->cmds->cmd->redir->next->rightmost = true;
		ms->cmds->cmd->redir->next->target = NULL;
		ms->cmds->cmd->redir->next->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->cmd->redir->next->target->filename = ft_strdup("file1");
		ms->cmds->cmd->redir->next->next = NULL;
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->next->rightmost = true;
		ms->cmds->next->cmd->redir->next->target = NULL;
		ms->cmds->next->cmd->redir->next->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->target->filename = ft_strdup("file2");
		ms->cmds->next->cmd->redir->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 3)
	{
		ft_printf("Test with ls -l > file1 | cat -e > file2 | wc -l > file3\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next->next->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("ls");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_outfile;
		ms->cmds->cmd->redir->target = NULL;
		ms->cmds->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->cmd->redir->target->filename = ft_strdup("file1");
		ms->cmds->cmd->redir->rightmost = true;
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->target = NULL;
		ms->cmds->next->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->target->filename = ft_strdup("file2");
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("wc");
		ms->cmds->next->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->next->cmd->words->next->next = NULL;
		ms->cmds->next->next->cmd->heredoc = 0;
ms->cmds->next->next->cmd->builtin = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->next->cmd->redir->target = NULL;
		ms->cmds->next->next->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->target->filename = ft_strdup("file3");
		ms->cmds->next->next->cmd->redir->rightmost = true;
		ms->be->nb_cmds = 3;
	}
	else if (case_nb == 4)  // case number 4 for "cat | cat | ls"
	{
		ft_printf_fd(2, "This command is not yet executed properly. It is a pipeline with 3 commands.\n");

		// Allocate first command (cat)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (cat)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (ls)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("ls");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->heredoc = 0;
ms->cmds->next->next->cmd->builtin = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->next->cmd->redir->next = NULL;

		// End of command chain
		ms->cmds->next->next->next = NULL;

		// Set the number of commands
		ms->be->nb_cmds = 3;  // 3 commands in the pipeline
	}
	else if (case_nb == 5)
	{
		ft_printf("Test with echo hello world | grep hello > output.txt\n");

		// First command: echo hello world
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("echo");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("hello");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("world");
		ms->cmds->cmd->words->next->next->next = NULL;
		ms->cmds->cmd->flags = 0;

		// Pipe to second command: grep hello
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("grep");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("hello");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->heredoc = 0;
		ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->cmd->redir->target = NULL;
		ms->cmds->next->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->target->filename = ft_strdup("output.txt");

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 6)
	{
		ft_printf("Test with cat < input.txt | sort | uniq\n");

		// First command: cat < input.txt
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");
		ms->cmds->cmd->words->next = NULL;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_infile;
		ms->cmds->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->cmd->redir->target->filename = ft_strdup("input.txt");
		ms->cmds->cmd->redir->rightmost = true;

		// Pipe to second command: sort
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("sort");
		ms->cmds->next->cmd->words->next = NULL;

		// Pipe to third command: uniq
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("uniq");
		ms->cmds->next->next->cmd->words->next = NULL;

		ms->cmds->next->next->next = NULL;
		ms->be->nb_cmds = 3;
	}
	else if (case_nb == 7)
	{
		ft_printf("Test with find . -type f | xargs grep TODO > todo_list.txt\n");

		// First command: find . -type f
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("find");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup(".");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("-type");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("f");
		ms->cmds->cmd->words->next->next->next->next = NULL;

		// Pipe to second command: xargs grep TODO
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("xargs");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("grep");
		ms->cmds->next->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->next->word = ft_strdup("TODO");
		ms->cmds->next->cmd->words->next->next->next = NULL;

		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->target = NULL;
		ms->cmds->next->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->target->filename = ft_strdup("todo_list.txt");
		ms->cmds->next->cmd->redir->rightmost = true;

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 8)
	{
		ft_printf("Test with mkdir new_folder | ls -l\n");

		// First command: mkdir new_folder
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("mkdir");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("new_folder");
		ms->cmds->cmd->words->next->next = NULL;

		// Pipe to second command: ls -l
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("ls");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->cmd->words->next->next = NULL;

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 9)
	{
		ft_printf("Test with tar -czf archive.tar.gz /new_folder | ls -l archive.tar.gz\n");

		// First command: tar -czf archive.tar.gz /new_folder
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("tar");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-czf");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("archive.tar.gz");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("/new_folder");
		ms->cmds->cmd->words->next->next->next->next = NULL;

		// Pipe to second command: ls -l archive.tar.gz
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("ls");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->next->word = ft_strdup("archive.tar.gz");
		ms->cmds->next->cmd->words->next->next->next = NULL;

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 10)
	{
		ft_printf("Test with echo $HOME > home_directory.txt\n");

		// First command: echo $HOME
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("echo");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("$HOME");
		ms->cmds->cmd->words->next->next = NULL;

		// Output redirection to home_directory.txt
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_outfile;
		ms->cmds->cmd->redir->rightmost = true;
		ms->cmds->cmd->redir->target = NULL;
		ms->cmds->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->cmd->redir->target->filename = ft_strdup("home_directory.txt");

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 11)
	{
		ft_printf("Test with ps aux | grep bash | wc -l\n");

		// First command: ps aux
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("ps");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("aux");
		ms->cmds->cmd->words->next->next = NULL;

		// Pipe to second command: grep bash
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("grep");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("bash");
		ms->cmds->next->cmd->words->next->next = NULL;

		// Pipe to third command: wc -l
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("wc");
		ms->cmds->next->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->next->cmd->words->next->next = NULL;

		ms->cmds->next->next->next = NULL;
		ms->be->nb_cmds = 3;
	}
	else if (case_nb == 12)
	{
		ft_printf("Test with cd /tmp | touch temp_file | ls -l temp_file\n");

		// First command: cd /tmp
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cd");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("/tmp");
		ms->cmds->cmd->words->next->next = NULL;

		// Pipe to second command: touch temp_file
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("touch");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("temp_file");
		ms->cmds->next->cmd->words->next->next = NULL;

		// Pipe to third command: ls -l temp_file
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("ls");
		ms->cmds->next->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->next->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->next->next->word = ft_strdup("temp_file");
		ms->cmds->next->next->cmd->words->next->next->next = NULL;

		ms->cmds->next->next->next = NULL;
		ms->be->nb_cmds = 3;
	}
	else if (case_nb == 13)
	{
		ft_printf("Test with cat command without further input\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");
		ms->cmds->cmd->words->next = NULL;
		ms->be->nb_cmds = 1;
		ms->cmds->cmd->flags = 0;
	}
		else if (case_nb == 14)  // case number 4 for "sjlfkdsjfs | dslkjsdlf | sljkdsdljf"
	{
		ft_printf_fd(2, "three fantasy commands to see behavior and error messages. It is a pipeline with 3 commands.\n");

		// Allocate first command (sjlfkdsjfs)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("sjlfkdsjfs");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (dslkjsdlf)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("dslkjsdlf");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (sljkdsdljf)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("sljkdsdljf");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->heredoc = 0;
ms->cmds->next->next->cmd->builtin = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->next->cmd->redir->next = NULL;

		// End of command chain
		ms->cmds->next->next->next = NULL;

		// Set the number of commands
		ms->be->nb_cmds = 3;  // 3 commands in the pipeline
	}
	else if (case_nb == 15)  // case number 15 for "make -j re"
	{
		ft_printf_fd(2, "case number 15 for \"make -j re\"\n");

		// Allocate first command (make -j)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("make");  // first command: make
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-j");  // additional argument: -j
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("re");  // additional argument: re
		ms->cmds->cmd->words->next->next->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 16) // case number 16 "make -j exv"
	{
		ft_printf_fd(2, "case number 16 for \"make -j exv\"\n");

		// Allocate first command (make -j)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("make");  // first command: make
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-j");  // additional argument: -j
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("exv");  // additional argument: exv
		ms->cmds->cmd->words->next->next->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 17) // case number 17 "make -j fclean"
	{
		ft_printf_fd(2, "case number 17 for \"make -j fclean\"\n");

		// Allocate first command (make -j)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("make");  // first command: make
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-j");  // additional argument: -j
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("fclean");  // additional argument: fclean
		ms->cmds->cmd->words->next->next->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 18) // case number 18 "./minishell"
	{
		ft_printf_fd(2, "case number 18 for \"./minishell\"\n");

		// Allocate first command (./minishell)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("./minishell");  // first command: ./minishell
		ms->cmds->cmd->words->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 19) // case number 19 "clear"
	{
		ft_printf_fd(2, "case number 19 for \"clear\"\n");

		// Allocate first command (clear)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("clear");  // first command: clear
		ms->cmds->cmd->words->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if (case_nb == 20) // case number 20 "<<eof cat | cat >hd_output1"
	{
		ft_printf_fd(2, "case number 20 for \"<<eof cat | cat >hd_output1\"\n");

		// Allocate first command (<<eof cat)
		ms->global_flags = 1;
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");  // first command: <<eof
		ms->cmds->cmd->words->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 1;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_here_doc;
		ms->cmds->cmd->redir->hd_del = ft_strdup("eof");
		ms->cmds->cmd->redir->rightmost = true;
		ms->cmds->cmd->redir->target = NULL;
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no further arguments
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->target->filename = ft_strdup("hd_output1");
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->next = NULL;
	}
	else if (case_nb == 21)  // case number 21 for "sjlfkdsjfs | cat | ls"
	{
		ft_printf_fd(2, "sjlfkdsjfs | cat | ls\n");

		// Allocate first command (sjlfkdsjfs)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("sjlfkdsjfs");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (dslkjsdlf)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (sljkdsdljf)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("ls");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->heredoc = 0;
ms->cmds->next->next->cmd->builtin = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->next->cmd->redir->next = NULL;

		// End of command chain
		ms->cmds->next->next->next = NULL;

		// Set the number of commands
		ms->be->nb_cmds = 3;  // 3 commands in the pipeline
	}
	else if (case_nb == 22) // case number 22 for "cat | sjlfkdsjfs | ls"
	{
		ft_printf_fd(2, "cat | sjlfkdsjfs | ls\n");

		// Allocate first command (sjlfkdsjfs)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (dslkjsdlf)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("sjlfkdsjfs");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->heredoc = 0;
ms->cmds->next->cmd->builtin = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me

		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (sljkdsdljf)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("ls");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->heredoc = 0;
ms->cmds->next->next->cmd->builtin = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->next->cmd->redir->next = NULL;

		// End of command chain
		ms->cmds->next->next->next = NULL;

		// Set the number of commands
		ms->be->nb_cmds = 3;  // 3 commands in the pipeline
	}
	else if (case_nb == 23)
	{
		ft_printf("23 - nc - l 80\n");

		// Allocate first command (make -j)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("nc");  // first command: make
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("-l");  // additional argument: -j
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("80");  // additional argument: re
		ms->cmds->cmd->words->next->next->next = NULL;  // no further arguments
		ms->cmds->cmd->flags = 0;
	}
	else if(case_nb == 24)
	{
		ft_printf("24 - print current stabs\n"); // [ ]
		ft_printf("Global_stab\n"); // [ ]
		ft_print_stab(ms, 1);
		if (ms->be->global_stabs->next)
		{
			ft_printf("local_stab\n"); // [ ]
			ft_print_stab(ms, 2);
		}
	}
	else if(case_nb == 25)
	{
		// case to add a new variable to the local stab
		ft_printf("25 - add new variable to local stab\n");
		if (ft_lookup_stab(ms->be->global_stabs->next, "NEW_VAR"))
		{
			ft_printf("variable NEW_VAR already exists in local stab\n");
			if (ft_upd_stab_val(ms->be->global_stabs->next, "NEW_VAR", "23061989"))
				ft_printf("variable NEW_VAR added to local stab\n");
			else
				ft_printf("variable NEW_VAR not added to local stab\n");
		}
		else
		{
			ft_printf("variable NEW_VAR does not exist in local stab\n");
			ft_add_local_val(ms, "NEW_VAR=23061989");
		}
		ft_printf("added variable NEW_VAR to local stab\n");
		ft_printf("the newly added Variable is: %s\n", ft_lookup_stab(ms->be->global_stabs->next, "NEW_VAR"));
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 26)
	{
		// case to make the variable NEW_VAR global
		ft_printf("26 - make variable NEW_VAR global\n");
		if (ft_lookup_stab(ms->be->global_stabs, "NEW_VAR"))
		{
			ft_printf("variable NEW_VAR already exists in global stab\n");
		}
		else
		{
			ft_printf("variable NEW_VAR does not exist in global stab\n");
			ft_printf("return val of ft_make_global = %d\n", ft_make_global(ms, "NEW_VAR"));
			ft_printf("the newly added Variable is: %s\n", ft_lookup_stab(ms->be->global_stabs, "NEW_VAR"));
		}
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 27)
	{
		// case to make the variable NEW_VAR global
		ft_printf("27 - add a new global variable\n");
		if (ft_lookup_stab(ms->be->global_stabs, "NEW_IN_GLOBAL"))
		{
			ft_printf("variable NEW_IN_GLOBAL already exists in global stab\n");
		}
		else
		{
			ft_add_global_val(ms, "NEW_IN_GLOBAL=thisisanewvar");
		}
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 28)
	{
		// case to add 20 new variables;
		int i = 0;
		char *nb_str;
		char *tmp;

		ft_printf("28 - add 20 new global variables\n");

		while (i < 20)
		{
			nb_str = ft_itoa(i);
			tmp = ft_multistrjoin(4, "NEW", nb_str, "=contentofNEW", nb_str);
			ft_add_global_val(ms, tmp);
			free(tmp);
			free(nb_str);
			i++;
		}
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 29)
	{
		// case to remove a variable from global
		ft_printf("29 - remove a global variable\n");
		ft_rem_fr_stab(ms->be->global_stabs, "NEW_VAR");
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 30)
	{
		// case to change a global val
		ft_printf("30 - change a global variable\n");
		ft_upd_stab_val(ms->be->global_stabs, "NEW_VAR", "new_val");
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 31)
	{
		// case to change a local val
		ft_printf("31 - change a local variable\n");
		ft_upd_stab_val(ms->be->global_stabs->next, "NEW_VAR", "new_val");
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 32)
	{
		// case to update a val at runtime
		ft_printf("32 - case to update a val at runtime\n");
		ft_update_envp_runtime(ft_create_envp(ms), "PATH", "./");
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 33)
	{
		// case to recall a val from stab
		ft_printf("33 - case to recall a val from stab\n");
		ft_printf("GFM_LANG is: %s\n",ft_lookup_stab(ms->be->global_stabs, "GDM_LANG"));
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if(case_nb == 34)
	{
		// case to recall a nonexistent val from stab
		ft_printf("34 - case to recall a nonexistent val from stab\n");
		ft_printf("DOESNTEXIST is: %s\n",ft_lookup_stab(ms->be->global_stabs, "DOESNTEXIST"));
		ft_printf("printing the stabs\n");
		ft_printf("printing the global stab:\n");
		ft_print_stab(ms, 1);
		ft_printf("printing the local stab:\n");
		ft_print_stab(ms, 2);
	}
	else if (case_nb == 35)
	{
		ft_printf("Test with echo klsjhdsdf klsjhdsdf klsjhdsdf > home_directory.txt\n");

		// First command: echo $HOME
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("echo");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next->next = NULL;


		// Output redirection to home_directory.txt
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_outfile;
		ms->cmds->cmd->redir->rightmost = true;
		ms->cmds->cmd->redir->target = NULL;
		ms->cmds->cmd->redir->target = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->cmd->redir->target->filename = ft_strdup("home_directory.txt");

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 36)
	{
		ft_printf("Test with echo klsjhdsdf klsjhdsdf klsjhdsdf\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("echo");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next->next = NULL;

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 37)
	{
		ft_printf("37 - Test with pwd klsjhdsdf klsjhdsdf klsjhdsdf\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("pwd");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("klsjhdsdf");
		ms->cmds->cmd->words->next->next->next->next = NULL;

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 38)
	{
		ft_printf("38 - Test with pwd without any further arguments\n");

		// First command: echo $HOME
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("pwd");
		ms->cmds->cmd->words->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 39)
	{
		ft_printf("39 - Test with cd ..\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cd");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("..");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 40)
	{
		ft_printf("40 - export\n");


		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 41)
	{
		ft_printf("41 - export new=bla\n");


		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("new=bla");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 42)
	{
		ft_printf("42 - export new2\n");



		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("new2");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
		else if (case_nb == 43)
	{
		ft_printf("43 - export new=bla\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("new=bla");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
		else if (case_nb == 44)
	{
		ft_printf("44 - export TEST1=20000 TEST2=30000 TEST3\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("TEST1=20000");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("TEST2=30000");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("TEST3");
		ms->cmds->cmd->words->next->next->next->next = NULL;

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
			else if (case_nb == 45)
	{
		ft_printf("45 - export empty=\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("export");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("empty=");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 46)
	{
		ft_printf("46 - unset non existent var \"NONEXISTENT\"\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("unset");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("NONEXISTENT");
		ms->cmds->cmd->words->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
		else if (case_nb == 47)
	{
		ft_printf("47 - unset NEW1 NEW2 NEW3 (execute debug case 28 before)\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("unset");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("NEW1");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("NEW2");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("NEW3");
		ms->cmds->cmd->words->next->next->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 48)
	{
		ft_printf("48 - env with no arguments\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("env");
		ms->cmds->cmd->words->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
		else if (case_nb == 49)
	{
		ft_printf("49 - env NEW1 NEW2 NEW3 should return error\n");

		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("env");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("NEW1");
		ms->cmds->cmd->words->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->word = ft_strdup("NEW2");
		ms->cmds->cmd->words->next->next->next = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->next->next->next->word = ft_strdup("NEW3");
		ms->cmds->cmd->words->next->next->next->next = NULL;
		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}

}

void	ft_debug(t_ms *ms)
{
	ft_deb_commands(ms);
}
