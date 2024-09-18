/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/18 12:57:51 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_deb_here_doc(t_ms *ms)
{
	setbuf(stdout, 0);
	ms->global_flags = 1;
	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	ms->cmds->next = NULL;
	ms->cmds->cmd->redir->next->next->next = NULL;
	ms->cmds->cmd->redir->from = NULL;
	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	ms->cmds->cmd->flags = 1;
	ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	ms->cmds->cmd->redir->instruction = redir_here_doc;
	ms->cmds->cmd->redir->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->from = NULL;
	ms->cmds->cmd->redir->next->next->from = NULL;
	ms->cmds->cmd->redir->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->next->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	ms->cmds->cmd->redir->next->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
}

void	ft_deb_commands(t_ms *ms)
{
	int case_nb;

	case_nb = INT_MIN;
	setbuf(stdout, 0);

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

	case_nb = ft_atoi(readline("Choose debug case: "));
	while (case_nb < 0 || case_nb > 20)
	{
		ft_printf("Error: wrong selection\n");
		case_nb = ft_atoi(readline("Choose debug case: "));
	}
	if (case_nb == 0)
	{
		ft_printf("Test with cat command and single input argument file\n");
		ms->cmd = ft_strdup("cat ./valgrind_line.txt");
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
		ms->cmd = ft_strdup("ls -l | cat -e");
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
		ms->cmds->next->cmd->flags = 0;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 2)
	{
		ft_printf("Test with ls -l > file1 | cat -e > file2\n");
		ms->cmd = ft_strdup("ls -l > file1 | cat -e > file2");
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
		ms->cmds->cmd->redir->instruction = redir_outpipe;
		ms->cmds->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->next->instruction = redir_outfile;
		ms->cmds->cmd->redir->next->rightmost = true;
		ms->cmds->cmd->redir->next->from = NULL;
		ms->cmds->cmd->redir->next->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->cmd->redir->next->to->filename = ft_strdup("file1");
		ms->cmds->cmd->redir->next->next = NULL;
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->next->rightmost = true;
		ms->cmds->next->cmd->redir->next->from = NULL;
		ms->cmds->next->cmd->redir->next->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->to->filename = ft_strdup("file2");
		ms->cmds->next->cmd->redir->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 3)
	{
		ms->cmd = ft_strdup("ls -l > file1 | cat -e > file2 | wc -l > file3");
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
		ms->cmds->cmd->redir->from = NULL;
		ms->cmds->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->cmd->redir->to->filename = ft_strdup("file1");
		ms->cmds->cmd->redir->rightmost = true;
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");
		ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
		ms->cmds->next->cmd->words->next->next = NULL;
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->from = NULL;
		ms->cmds->next->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->to->filename = ft_strdup("file2");
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("wc");
		ms->cmds->next->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->next->next->cmd->words->next->word = ft_strdup("-l");
		ms->cmds->next->next->cmd->words->next->next = NULL;
		ms->cmds->next->next->cmd->flags = 0;
		ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->next->cmd->redir->from = NULL;
		ms->cmds->next->next->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->next->cmd->redir->to->filename = ft_strdup("file3");
		ms->cmds->next->next->cmd->redir->rightmost = true;
		ms->be->nb_cmds = 3;
	}
	else if (case_nb == 4)  // case number 4 for "cat | cat | ls"
	{
		ft_printf_err("This command is not yet executed properly. It is a pipeline with 3 commands.");
		ms->cmd = ft_strdup("cat | cat | ls");

		// Allocate first command (cat)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_outpipe;
		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (cat)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->instruction = redir_outpipe;
		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (ls)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("ls");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->flags = 0;
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
		ms->cmd = ft_strdup("echo hello world | grep hello > output.txt");

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
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->cmd->redir->from = NULL;
		ms->cmds->next->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->to->filename = ft_strdup("output.txt");

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 6)
	{
		ms->cmd = ft_strdup("cat < input.txt | sort | uniq");

		// First command: cat < input.txt
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");
		ms->cmds->cmd->words->next = NULL;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1);  // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_infile;
		ms->cmds->cmd->redir->from = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->cmd->redir->from->filename = ft_strdup("input.txt");
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
		ms->cmd = ft_strdup("find . -type f | xargs grep \"[ ]\" > todo_list.txt");

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
		ms->cmds->next->cmd->redir->from = NULL;
		ms->cmds->next->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->next->cmd->redir->to->filename = ft_strdup("todo_list.txt");
		ms->cmds->next->cmd->redir->rightmost = true;

		ms->cmds->next->next = NULL;
		ms->be->nb_cmds = 2;
	}
	else if (case_nb == 8)
	{
		ms->cmd = ft_strdup("mkdir new_folder | ls -l");

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
		ms->cmd = ft_strdup("tar -czf archive.tar.gz /new_folder | ls -l archive.tar.gz");

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
		ms->cmd = ft_strdup("echo $HOME > home_directory.txt");

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
		ms->cmds->cmd->redir->from = NULL;
		ms->cmds->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1);  // [ ] free me
		ms->cmds->cmd->redir->to->filename = ft_strdup("home_directory.txt");

		ms->cmds->next = NULL;
		ms->be->nb_cmds = 1;
	}
	else if (case_nb == 11)
	{
		ms->cmd = ft_strdup("ps aux | grep bash | wc -l");

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
		ms->cmd = ft_strdup("cd /tmp | touch temp_file | ls -l temp_file");

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
		ms->cmd = ft_strdup("cat");
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
		ft_printf_err("three fantasy commands to see behavior and error messages. It is a pipeline with 3 commands.");
		ms->cmd = ft_strdup("sjlfkdsjfs | dslkjsdlf | sljkdsdljf");

		// Allocate first command (sjlfkdsjfs)
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("sjlfkdsjfs");  // first command: cat
		ms->cmds->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->cmd->flags = 0;
		ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->cmd->redir->instruction = redir_outpipe;
		ms->cmds->cmd->redir->next = NULL;

		// Allocate second command (dslkjsdlf)
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("dslkjsdlf");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_inpipe;
		ms->cmds->next->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->next->instruction = redir_outpipe;
		ms->cmds->next->cmd->redir->next->next = NULL;

		// Allocate third command (sljkdsdljf)
		ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->next->cmd->words->word = ft_strdup("sljkdsdljf");  // third command: ls
		ms->cmds->next->next->cmd->words->next = NULL;  // no additional arguments
		ms->cmds->next->next->cmd->flags = 0;
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
		ft_printf_err("case number 15 for \"make -j re\"");
		ms->cmd = ft_strdup("make -j re");

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
		ft_printf_err("case number 16 for \"make -j exv\"");
		ms->cmd = ft_strdup("make -j exv");

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
		ft_printf_err("case number 17 for \"make -j fclean\"");
		ms->cmd = ft_strdup("make -j fclean");

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
		ft_printf_err("case number 18 for \"./minishell\"");
		ms->cmd = ft_strdup("./minishell");

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
		ft_printf_err("case number 19 for \"clear\"");
		ms->cmd = ft_strdup("clear");

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
		ft_printf_err("case number 20 for \"<<eof cat | cat >hd_output1\"\n");
		ms->cmd = ft_strdup("<<eof cat | cat >hd_output1");

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
		ms->cmds->cmd->redir->from = NULL;
		ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1);  // [ ] free me
		ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1);  // [ ] free me
		ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1);  // [ ] free me
		ms->cmds->next->cmd->words->word = ft_strdup("cat");  // second command: cat
		ms->cmds->next->cmd->words->next = NULL;  // no further arguments
		ms->cmds->next->cmd->flags = 0;
		ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
		ms->cmds->next->cmd->redir->instruction = redir_outfile;
		ms->cmds->next->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
		ms->cmds->next->cmd->redir->to->filename = ft_strdup("hd_output1");
		ms->cmds->next->cmd->redir->rightmost = true;
		ms->cmds->next->cmd->redir->from = NULL;
		ms->cmds->next->next = NULL;
	}
}

void	ft_debug(t_ms *ms)
{
	char	*mode;

	printf("Debug cases:\n");
	printf("0 - here_doc\n");
	printf("1 - command_execution\n");
	mode = readline("Choose debug case: ");

	if (strncmp(mode, "0", 8) == 0 && ft_strlen(mode) == 1)
		ft_deb_here_doc(ms);
	else if (strncmp(mode, "1", 1) == 0
		&& ft_strlen(mode) == 1)
		ft_deb_commands(ms);
	else
		printf("Error: wrong selection\n");
}
