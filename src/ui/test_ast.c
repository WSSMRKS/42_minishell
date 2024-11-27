
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../headers/minishell.h"

#define NUM_TEST_STRINGS ((int)(sizeof(test_str) / sizeof(test_str[0])) - 1)
#define NUM_TEST_SEP ((int)(sizeof(test_sep) / sizeof(test_sep[0])) - 1)
#define NUM_TEST_OPS ((int)(sizeof(test_ops) / sizeof(test_ops[0])) - 1)

// can be with double quotes, single quotes, without quotes, with env var, with $? etc
static const char *test_str[] = {
	// "normal",
	// "\"double quotes\"",
	// "\'single quotes\'",
	// "normal$XDG_CURRENT_DESKTOP",
	// "normal\\ $XDG_CURRENT_DESKTOP",
	// "normal\\$XDG_CURRENT_DESKTOP",
	// "\"double quotes\"$XDG_CURRENT_DESKTOP",
	// "\"double quotes\"\\ $XDG_CURRENT_DESKTOP",
	// "\"double quotes\"\\$XDG_CURRENT_DESKTOP",
	// "\'single quotes\'$XDG_CURRENT_DESKTOP",
	// "\'single quotes\'\\ $XDG_CURRENT_DESKTOP",
	// "\'single quotes\'\\$XDG_CURRENT_DESKTOP",
	// "\'single $XDG_CURRENT_DESKTOP quotes\'$XDG_CURRENT_DESKTOP",
	"\'single $XDG_CURRENT_DESKTOP quotes\'\\ $XDG_CURRENT_DESKTOP",
	"\'single $XDG_CURRENT_DESKTOP quotes\'\\$XDG_CURRENT_DESKTOP",
	"\"double$XDG_CURRENT_DESKTOP quotes\"$XDG_CURRENT_DESKTOP",
	"\"double$XDG_CURRENT_DESKTOP quotes\"\\ $XDG_CURRENT_DESKTOP",
	"\"double$XDG_CURRENT_DESKTOP quotes\"\\$XDG_CURRENT_DESKTOP",
	"\"double quotes \"with' single quotes '\\ and\\ spaces\\ without\\ quotes",
	0
};

static const char *test_str_expected[] = {
	// "normal",
	// "double quotes",
	// "single quotes",
	// "normalGNOME",
	// "normal GNOME",
	// "normal$XDG_CURRENT_DESKTOP",
	// "double quotesGNOME",
	// "double quotes GNOME",
	// "double quotes$XDG_CURRENT_DESKTOP",
	// "single quotesGNOME",
	// "single quotes GNOME",
	// "single quotes$XDG_CURRENT_DESKTOP",
	// "single $XDG_CURRENT_DESKTOP quotesGNOME",
	"single $XDG_CURRENT_DESKTOP quotes GNOME",
	"single $XDG_CURRENT_DESKTOP quotes$XDG_CURRENT_DESKTOP",
	"doubleGNOME quotesGNOME",
	"doubleGNOME quotes GNOME",
	"doubleGNOME quotes$XDG_CURRENT_DESKTOP",
	"double quotes with single quotes  and spaces without quotes",
	0
};

static const char *test_sep[] = {
	" ",
	"\t",
	0
};

// Helper function to get next separator in rotation
static const char *get_next_sep(int *sep_index) {
    const char *sep = test_sep[*sep_index];
    *sep_index = (*sep_index + 1) % NUM_TEST_SEP;
    return sep;
}

static const char *test_ops[] = {
	">",
	"<",
	">>",
	"<<",
	0
};

char **build_ops(bool include_no_arg_ops) {
    // Calculate total number of combinations
    int total = 0;
    if (include_no_arg_ops) {
        total += NUM_TEST_OPS; // Operators without arguments
    }
    total += NUM_TEST_OPS * NUM_TEST_STRINGS; // Operators with one argument

    // Allocate array of string pointers plus one for NULL terminator
    char **result = malloc((total + 1) * sizeof(char *));
    if (!result) return NULL;

    int idx = 0;

    // Generate operators without arguments if requested
    if (include_no_arg_ops) {
        for (int i = 0; i < NUM_TEST_OPS; i++) {
            char *op = strdup(test_ops[i]);
            if (!op) {
                // Clean up and return on allocation failure
                for (int j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            result[idx++] = op;
        }
    }

    // Generate operators with one argument
    for (int i = 0; i < NUM_TEST_OPS; i++) {
        for (int j = 0; j < NUM_TEST_STRINGS; j++) {
            // Calculate length needed for operator + argument + space + null terminator
            int len = strlen(test_ops[i]) + strlen(test_str[j]) + 2;
            char *op = malloc(len);
            if (!op) {
                // Clean up and return on allocation failure
                for (int k = 0; k < idx; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            sprintf(op, "%s %s", test_ops[i], test_str[j]);
            result[idx++] = op;
        }
    }

    // NULL terminate the array
    result[idx] = NULL;

    return result;
}


char **build_cmds(int maxargs) {
    // Calculate total number of combinations
    int total = 0;
    for (int nargs = 0; nargs <= maxargs; nargs++) {
        // For each number of arguments:
        // - First position (command) can be any test string
        // - Each argument position can be any test string
        // - Each separator position can be any separator or empty
        // - Can have separator before first and after last (4 combinations)
        int combinations = NUM_TEST_STRINGS;  // for command
        for (int i = 0; i < nargs; i++) {
            combinations *= NUM_TEST_STRINGS;  // for each argument
        }
        // Multiply by separator combinations:
        // - Between each word: (NUM_TEST_SEP + 1) options
        // - Before first and after last: 4 combinations
        combinations *= pow(NUM_TEST_SEP + 1, nargs + 1) * 4;
        total += combinations;
    }

    // Allocate array of string pointers plus one for NULL terminator
    char **result = malloc((total + 1) * sizeof(char *));
    if (!result) return NULL;

    int idx = 0;  // Current position in result array

    // Generate all combinations for each number of arguments
    for (int nargs = 0; nargs <= maxargs; nargs++) {
        // Calculate positions needed
        int word_positions = nargs + 1;  // command + args
        int sep_positions = nargs + 1;   // between words + before/after

        // Create arrays to track current indices
        int *word_indices = calloc(word_positions, sizeof(int));
        int *sep_indices = calloc(sep_positions, sizeof(int));
        if (!word_indices || !sep_indices) {
            free(word_indices);
            free(sep_indices);
            for (int i = 0; i < idx; i++) free(result[i]);
            free(result);
            return NULL;
        }

        // Generate all combinations
        int done = 0;
        while (!done) {
            // For each separator combination
            int sep_done = 0;
            while (!sep_done) {
                // For each before/after combination (00, 01, 10, 11)
                for (int before = 0; before <= 1; before++) {
                    for (int after = 0; after <= 1; after++) {
                    	// Calculate required length
                    	int len = 0;
                    	if (before && sep_indices[0] < NUM_TEST_SEP) {  // Changed condition
                    	    len += strlen(test_sep[sep_indices[0]]);
                    	}
                    	for (int i = 0; i < word_positions; i++) {
                    	    len += strlen(test_str[word_indices[i]]);
                    	    if (i < word_positions - 1 || after) {
                    	        if (sep_indices[i] < NUM_TEST_SEP) {  // Changed condition
                    	            len += strlen(test_sep[sep_indices[i]]);
                    	        }
                    	    }
                    	}

                        // Allocate and build string
                        char *cmd = malloc(len + 1);
                        if (!cmd) {
                            free(word_indices);
                            free(sep_indices);
                            for (int i = 0; i < idx; i++) free(result[i]);
                            free(result);
                            return NULL;
                        }

                        // Build command string
                        int pos = 0;

                        // Add leading separator if needed
                        if (before && sep_indices[0] < NUM_TEST_SEP) {
                            strcpy(cmd + pos, test_sep[sep_indices[0]]);
                            pos += strlen(test_sep[sep_indices[0]]);
                        }

                        // Add words and separators
                        for (int i = 0; i < word_positions; i++) {
                            strcpy(cmd + pos, test_str[word_indices[i]]);
                            pos += strlen(test_str[word_indices[i]]);

                            if (i < word_positions - 1 || after) {
                                if (sep_indices[i] < NUM_TEST_SEP) {
                                    strcpy(cmd + pos, test_sep[sep_indices[i]]);
                                    pos += strlen(test_sep[sep_indices[i]]);
                                }
                            }
                        }

                        cmd[pos] = '\0';
                        result[idx++] = cmd;
                    }
                }

                // Move to next separator combination
                int j;
                for (j = sep_positions - 1; j >= 0; j--) {
                    sep_indices[j]++;
                    if (sep_indices[j] <= NUM_TEST_SEP) {  // This condition needs to change to:
                    	if (sep_indices[j] <= NUM_TEST_SEP - 1) {  // Changed condition
                    	    break;
                    	}
                    	sep_indices[j] = 0;
                    }
                }
                if (j < 0) sep_done = 1;
            }

            // Move to next word combination
            int j;
            for (j = word_positions - 1; j >= 0; j--) {
                word_indices[j]++;
                if (word_indices[j] < NUM_TEST_STRINGS) break;
                word_indices[j] = 0;
            }
            if (j < 0) done = 1;
        }

        free(word_indices);
        free(sep_indices);
    }

    // NULL terminate the array
    result[idx] = NULL;

    return result;
}

char **build_cmds_with_ops(int maxargs) {
    // First get all basic commands
    char **base_cmds = build_cmds(maxargs);
    if (!base_cmds) return NULL;

    // Count base commands
    int base_count = 0;
    while (base_cmds[base_count]) base_count++;

    // Get all operator combinations
    char **ops = build_ops(false);
    if (!ops) {
        for (int i = 0; i < base_count; i++) free(base_cmds[i]);
        free(base_cmds);
        return NULL;
    }

    // Count operator combinations
    int ops_count = 0;
    while (ops[ops_count]) ops_count++;

    // Calculate total combinations:
    // - Each command can have 0 or more operators before it
    // - Each command can have 0 or more operators after it
    // - Plus the original commands without operators
    int total = base_count;  // Original commands
    total += base_count * ops_count * 2;  // Commands with one operator (before or after)
    total += base_count * ops_count * ops_count;  // Commands with operators on both sides

    // Allocate result array
    char **result = malloc((total + 1) * sizeof(char *));
    if (!result) {
        for (int i = 0; i < base_count; i++) free(base_cmds[i]);
        free(base_cmds);
        for (int i = 0; i < ops_count; i++) free(ops[i]);
        free(ops);
        return NULL;
    }

    int idx = 0;

    // Add original commands without operators
    for (int i = 0; i < base_count; i++) {
        char *cmd = strdup(base_cmds[i]);
        if (!cmd) {
            // Handle allocation failure
            for (int j = 0; j < idx; j++) free(result[j]);
            free(result);
            for (int j = 0; j < base_count; j++) free(base_cmds[j]);
            free(base_cmds);
            for (int j = 0; j < ops_count; j++) free(ops[j]);
            free(ops);
            return NULL;
        }
        result[idx++] = cmd;
    }

    int sep_index = 0;  // Add this to track separator rotation

    // Add commands with one operator before
        for (int i = 0; i < base_count; i++) {
            for (int j = 0; j < ops_count; j++) {
                const char *sep = get_next_sep(&sep_index);
                int len = strlen(ops[j]) + strlen(sep) + strlen(base_cmds[i]) + 1;
                char *cmd = malloc(len);
                if (!cmd) {
                    // Handle allocation failure...
                }
                sprintf(cmd, "%s%s%s", ops[j], sep, base_cmds[i]);
                result[idx++] = cmd;
            }
        }

        // Add commands with one operator after
            for (int i = 0; i < base_count; i++) {
                for (int j = 0; j < ops_count; j++) {
                    const char *sep = get_next_sep(&sep_index);
                    int len = strlen(base_cmds[i]) + strlen(sep) + strlen(ops[j]) + 1;
                    char *cmd = malloc(len);
                    if (!cmd) {
                        // Handle allocation failure...
                    }
                    sprintf(cmd, "%s%s%s", base_cmds[i], sep, ops[j]);
                    result[idx++] = cmd;
                }
            }

            // Add commands with operators on both sides
                for (int i = 0; i < base_count; i++) {
                    for (int j = 0; j < ops_count; j++) {
                        for (int k = 0; k < ops_count; k++) {
                            const char *sep1 = get_next_sep(&sep_index);
                            const char *sep2 = get_next_sep(&sep_index);
                            int len = strlen(ops[j]) + strlen(sep1) + strlen(base_cmds[i]) +
                                     strlen(sep2) + strlen(ops[k]) + 1;
                            char *cmd = malloc(len);
                            if (!cmd) {
                                // Handle allocation failure...
                            }
                            sprintf(cmd, "%s%s%s%s%s", ops[j], sep1, base_cmds[i], sep2, ops[k]);
                            result[idx++] = cmd;
                        }
                    }
                }

    // NULL terminate the result array
    result[idx] = NULL;

    // Clean up temporary arrays
    for (int i = 0; i < base_count; i++) free(base_cmds[i]);
    free(base_cmds);
    for (int i = 0; i < ops_count; i++) free(ops[i]);
    free(ops);

    return result;
}

void	stab_add_val(t_ms *ms, t_stab_st *st, char *env)
{
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	val = ft_strdup(&env[i + 1]);
	if (ft_lookup_stab(st, key) != NULL)
	{
		ft_upd_stab_val(st, key, val);
		free(val);
		free(key);
	}
	else
		ft_add_to_stab(ms, st, key, val);
}

t_stab_st	init_stab(char **envp)
{
	size_t			i;
	t_stab_st	st;

	i = 0;
	while (envp[i])
		i++;
	st = (t_stab_st){0};
	st.size = ft_calc_stab_size(i);
	st.load_factor = 0;
	st.level = 1;
	st.stab = ft_calloc(sizeof(char *), st.size);
	i = 0;
	while (envp[i])
		stab_add_val(&st, envp[i++]);
	return (st);
}

t_ast *ast_from_line(char *line, char **envp, size_t *out_len)
{
    t_vec tokens;
    t_vec ast;
    t_ast *result;
    t_stab_st st;

    if (!line || !out_len || !envp)
        return NULL;
    *out_len = 0;

    // Initialize symbol table with environment variables
    st = init_stab(envp);

    // Initial tokenization
    tokens = tokenize(cstr_view(line));
    if (tokens.mem_err)
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // No tokens found
    if (tokens.len == 0)
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // Expand variables
    expand_vars(&tokens, &st);
    if (tokens.mem_err)
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // Unescape characters
    unescape_chars(&tokens);
    if (tokens.mem_err)
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // Normalize tokens
    tokens_normalize(&tokens);
    if (tokens.mem_err)
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // Convert tokens to AST
    if (!tokens_to_ast(&tokens, &ast))
    {
        vec_destroy(&tokens, NULL);
        return NULL;
    }

    // Clean up tokens as they're no longer needed
    vec_destroy(&tokens, NULL);

    // Handle empty AST
    if (ast.len == 0)
    {
        vec_destroy(&ast, NULL);
        return NULL;
    }

    // Convert vec to array
    *out_len = ast.len;
    result = vec_take(&ast);
    if (!result)
    {
        vec_destroy(&ast, NULL);
        return NULL;
    }

    return result;
}


void dbg_print_ast_arr(t_ast *ast, size_t len) {
    if (!ast) {
        printf("AST array is NULL\n");
        return;
    }

    printf("AST Array (length: %zu):\n", len);
    for (size_t i = 0; i < len; i++) {
        printf("Node[%zu]: ", i);

        if (ast[i].ty == AST_CMD) {
            printf("Type: CMD\n  Arguments: ");
            if (!ast[i].cmd) {
                printf("(NULL)\n");
            } else {
                printf("\n");
                for (int j = 0; ast[i].cmd[j]; j++) {
                    printf("    [%d]: \"%s\"\n", j, ast[i].cmd[j]);
                }
            }
        }
        else if (ast[i].ty == AST_OP) {
            printf("Type: OP\n  Operator: ");
            switch (ast[i].op.ty) {
                case OP_PIPE:
                    printf("PIPE");
                    break;
                case OP_REDIRECT:
                    printf("REDIRECT (>)");
                    break;
                case OP_INP_REDIRECT:
                    printf("INPUT REDIRECT (<)");
                    break;
                case OP_APPEND:
                    printf("APPEND (>>)");
                    break;
                case OP_HEREDOC:
                    printf("HEREDOC (<<)");
                    break;
                default:
                    printf("UNKNOWN");
            }
            printf("\n  Argument: %s\n",
                   ast[i].op.arg ? ast[i].op.arg : "(NULL)");
        }
        else {
            printf("Type: UNKNOWN (%d)\n", ast[i].ty);
        }
        printf("\n");
    }
    printf("End of AST Array\n");
}


void run_ast_tests() {
    char **test_lines = build_cmds_with_ops(2);
    if (!test_lines) {
        printf("Failed to build test lines\n");
        return;
    }

    // Create a minimal environment for testing
    char *test_env[] = {
        "XDG_CURRENT_DESKTOP=GNOME",
        NULL
    };

    for (int i = 0; test_lines[i]; i++) {
        printf("\n=== Test Case %d ===\n", i + 1);
        printf("Input line: %s\n", test_lines[i]);

        size_t ast_len = 0;
        t_ast *ast = ast_from_line(test_lines[i], test_env, &ast_len);
        if (!ast) {
            printf("Result: FAIL (NULL ast)\n");
            printf("===========================\n");
            continue;
        }

        dbg_print_ast_arr(ast, ast_len);

        bool found_match = false;
        for (size_t j = 0; j < ast_len; j++) {
            if (ast[j].ty == AST_CMD && ast[j].cmd) {
                for (int k = 0; ast[j].cmd[k]; k++) {
                    for (int m = 0; test_str_expected[m]; m++) {
                        if (strcmp(ast[j].cmd[k], test_str_expected[m]) == 0) {
                            found_match = true;
                            break;
                        }
                    }
                }
            }
            else if (ast[j].ty == AST_OP && ast[j].op.arg) {
                for (int m = 0; test_str_expected[m]; m++) {
                    if (strcmp(ast[j].op.arg, test_str_expected[m]) == 0) {
                        found_match = true;
                        break;
                    }
                }
            }
        }

        printf("Result: %s\n", found_match ? "OK" : "FAIL");
        printf("===========================\n");

        // Free the AST (assuming you have a function for this)
        // free_ast(ast);
    }

    // Free test lines
    for (int i = 0; test_lines[i]; i++) {
        free(test_lines[i]);
    }
    free(test_lines);
}

int main() {
    run_ast_tests();
    return 0;
}
