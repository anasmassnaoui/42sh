# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myamani <myamani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/14 11:19:14 by hbenlarh          #+#    #+#              #
#    Updated: 2020/02/17 16:13:32 by myamani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

OBJS_DIR = objs
LIBFT_HEADER = -I libft/
SRCS_SH_DIR = shell/srcs/execution
SRCS_JB_DIR = shell/srcs/execution/jobs
SRCS_CH_DIR = shell/srcs/execution/command_handler
SRCS_HA_DIR = shell/srcs/hash
SRCS_RL_DIR = readline/srcs/readline
SRCS_HI_DIR = readline/srcs/history
SRCS_GL_DIR = readline/srcs/globing
SRCS_AC_DIR = readline/srcs/autocomplete
SRCS_PR_DIR = shell/srcs/parsin
INCS_RL_DIR = -I readline/includes/ $(LIBFT_HEADER)
INCS_SH_DIR = -I shell/includes/ $(INCS_RL_DIR)
LIBS_DIR = libft/libft.a -ltermcap


SRCS_HA = $(SRCS_HA_DIR)/add_in_hash.c \
		  $(SRCS_HA_DIR)/display_hash.c \
		  $(SRCS_HA_DIR)/hash_flags.c

SRCS_RL = $(SRCS_RL_DIR)/arrow.c \
		  $(SRCS_RL_DIR)/arrow_suite.c \
		  $(SRCS_RL_DIR)/commande.c \
		  $(SRCS_RL_DIR)/copy.c \
		  $(SRCS_RL_DIR)/copy_selection.c \
		  $(SRCS_RL_DIR)/copy_suite.c \
		  $(SRCS_RL_DIR)/cursor.c \
		  $(SRCS_RL_DIR)/cut_selection.c \
		  $(SRCS_RL_DIR)/cut_selection_suite.c \
		  $(SRCS_RL_DIR)/general.c \
		  $(SRCS_RL_DIR)/line.c \
		  $(SRCS_RL_DIR)/last_col.c \
		  $(SRCS_RL_DIR)/readline.c\
		  $(SRCS_RL_DIR)/move_cursor.c \
		  $(SRCS_RL_DIR)/move_word.c \
		  $(SRCS_RL_DIR)/multiline.c \
		  $(SRCS_RL_DIR)/multiline_count.c \
		  $(SRCS_RL_DIR)/parse.c \
		  $(SRCS_RL_DIR)/terminal.c \
		  $(SRCS_RL_DIR)/rl_envirement.c \
		  $(SRCS_RL_DIR)/fc_execution.c \
		  $(SRCS_RL_DIR)/ctr_r_handle.c \
		  $(SRCS_RL_DIR)/ctr_r_handle_bis.c \
		  $(SRCS_RL_DIR)/readline_bis.c \
		  $(SRCS_RL_DIR)/readline_three.c \

SRCS_HI = $(SRCS_HI_DIR)/search_in_history.c \
          $(SRCS_HI_DIR)/get_next_line.c \
		  $(SRCS_HI_DIR)/store_line.c \
		  $(SRCS_HI_DIR)/history1.c\
		  $(SRCS_HI_DIR)/check_in_list.c \
		  $(SRCS_HI_DIR)/fc_command.c \
		  $(SRCS_HI_DIR)/fc_s.c \
		  $(SRCS_HI_DIR)/fc_e.c \
		  $(SRCS_HI_DIR)/fc_ln.c \
		  $(SRCS_HI_DIR)/copy_reverse_lst.c \
		  $(SRCS_HI_DIR)/print_hist.c \
		  $(SRCS_HI_DIR)/fc_reverse.c \
		  $(SRCS_HI_DIR)/fc_ln_reverse.c \
		  $(SRCS_HI_DIR)/fc_command_one.c \
		  $(SRCS_HI_DIR)/free_list_hist.c \
		  $(SRCS_HI_DIR)/fc_e_exec.c \
		  $(SRCS_HI_DIR)/check_in_list1.c \
		  $(SRCS_HI_DIR)/shell_sub.c \
		  $(SRCS_HI_DIR)/fc_flags1.c \
		  $(SRCS_HI_DIR)/path_exec.c \
		  $(SRCS_HI_DIR)/which_one_index.c \
		  $(SRCS_HI_DIR)/history_part.c 

SRCS_AC = $(SRCS_AC_DIR)/display.c \
		  $(SRCS_AC_DIR)/generale_auto.c \
		  $(SRCS_AC_DIR)/get_suggestion.c \
		  $(SRCS_AC_DIR)/ground.c \
		  $(SRCS_AC_DIR)/ground_bis.c \
		  $(SRCS_AC_DIR)/moveintab.c \
		  $(SRCS_AC_DIR)/quit_auto_mode.c \
		  $(SRCS_AC_DIR)/suggestion.c \
		  $(SRCS_AC_DIR)/display_and_move.c \
		  $(SRCS_AC_DIR)/displaytmpstr.c \
		  $(SRCS_AC_DIR)/sort_liste.c \
		  $(SRCS_AC_DIR)/path.c \
		  $(SRCS_AC_DIR)/free_autocmp.c \
		  $(SRCS_AC_DIR)/plus_funct.c \

SRCS_GL = $(SRCS_GL_DIR)/find_match.c \
		  $(SRCS_GL_DIR)/ft_joinchar.c \
		  $(SRCS_GL_DIR)/get_hint_and_dirs.c \
		  $(SRCS_GL_DIR)/wild_beast.c \
		  $(SRCS_GL_DIR)/wild_cards_lst_create.c \
		  $(SRCS_GL_DIR)/brackets_glob.c \
		  $(SRCS_GL_DIR)/glob_extras.c \
		  $(SRCS_GL_DIR)/wild_check.c \
		  $(SRCS_GL_DIR)/wild_file.c \


SRCS_SH = $(SRCS_SH_DIR)/execute.c \
		  $(SRCS_SH_DIR)/builtin_cmds.c \
		  $(SRCS_SH_DIR)/builtin_extention.c \
		  $(SRCS_SH_DIR)/child_pid_sys_cmd.c \
		  $(SRCS_SH_DIR)/ft_type.c \
		  $(SRCS_SH_DIR)/list.c \
		  $(SRCS_SH_DIR)/list_1.c \
		  $(SRCS_SH_DIR)/shell.c \
		  $(SRCS_SH_DIR)/own_cmds.c \
		  $(SRCS_SH_DIR)/srcs.c \
		  $(SRCS_SH_DIR)/sec_count.c \
		  $(SRCS_SH_DIR)/darlin.c \
		  $(SRCS_SH_DIR)/free.c \
		  $(SRCS_SH_DIR)/redirection_master.c \
		  $(SRCS_SH_DIR)/errors.c \
		  $(SRCS_SH_DIR)/childs.c \
		  $(SRCS_SH_DIR)/syntax_error.c \
		  $(SRCS_SH_DIR)/more_syntax_error.c \
		  $(SRCS_SH_DIR)/ft_shell_strsplit.c\
		  $(SRCS_SH_DIR)/alias.c\
		  $(SRCS_SH_DIR)/alias_list_manage.c\
		  $(SRCS_SH_DIR)/alias_addons.c \
		  $(SRCS_SH_DIR)/alias_display.c \
		  $(SRCS_SH_DIR)/export.c \
		  $(SRCS_SH_DIR)/export1.c \
		  $(SRCS_SH_DIR)/export2.c \
		  $(SRCS_SH_DIR)/export3.c \
		  $(SRCS_SH_DIR)/export4.c \
		  $(SRCS_SH_DIR)/modulo.c \
		  $(SRCS_SH_DIR)/hashtag.c \
		  $(SRCS_SH_DIR)/do_symbols1.c \
		  $(SRCS_SH_DIR)/get_expansions.c \
		  $(SRCS_SH_DIR)/is_symbols.c \
		  $(SRCS_SH_DIR)/copy_env.c \
		  $(SRCS_SH_DIR)/set.c \
		  $(SRCS_SH_DIR)/to_reset_hash.c \
		  $(SRCS_SH_DIR)/check_symbols.c \
		  $(SRCS_SH_DIR)/ft_cd.c \
		  $(SRCS_SH_DIR)/cd_path_manager.c \
		  $(SRCS_SH_DIR)/cd_flag.c \
		  $(SRCS_SH_DIR)/cd_env_update.c \
		  $(SRCS_SH_DIR)/ft_echo.c \
		  $(SRCS_SH_DIR)/echo_ripper.c \
		  $(SRCS_SH_DIR)/ft_exit.c \
		  $(SRCS_SH_DIR)/exit_bastard.c \
		  $(SRCS_SH_DIR)/shell_substitution_complements.c \
		  $(SRCS_SH_DIR)/preparse_check.c \
		  $(SRCS_SH_DIR)/aggregation.c \
		  $(SRCS_SH_DIR)/hash_temporaire_env.c \
		  $(SRCS_SH_DIR)/weird_syntax_error.c \
		  $(SRCS_SH_DIR)/ft_fc.c \
		  $(SRCS_SH_DIR)/env.c \
		  $(SRCS_SH_DIR)/shell_addons.c \

SRCS_JB = $(SRCS_JB_DIR)/fg_bg_jobs.c \
		  $(SRCS_JB_DIR)/fg_bg.c \
		  $(SRCS_JB_DIR)/groups.c \
		  $(SRCS_JB_DIR)/jobs.c \
		  $(SRCS_JB_DIR)/message.c \
		  $(SRCS_JB_DIR)/process_group.c \
		  $(SRCS_JB_DIR)/process.c \
		  $(SRCS_JB_DIR)/signal_name.c

SRCS_CH = $(SRCS_CH_DIR)/additional.c \
		  $(SRCS_CH_DIR)/command_handler.c \
		  $(SRCS_CH_DIR)/execute_command.c \
		  $(SRCS_CH_DIR)/signals.c \

SRCS_PR = $(SRCS_PR_DIR)/extras.c \
		  $(SRCS_PR_DIR)/more_extras.c \
		  $(SRCS_PR_DIR)/parsin.c \
		  $(SRCS_PR_DIR)/dollar.c \
		  $(SRCS_PR_DIR)/dollar_addons.c \
		  $(SRCS_PR_DIR)/count.c \
		  $(SRCS_PR_DIR)/check.c \
		  $(SRCS_PR_DIR)/token.c \
		  $(SRCS_PR_DIR)/info.c \
		  $(SRCS_PR_DIR)/escape_n_quote.c \
		  $(SRCS_PR_DIR)/lst_make.c \
		  $(SRCS_PR_DIR)/add_funcs.c \
		  $(SRCS_PR_DIR)/mc.c \
		  $(SRCS_PR_DIR)/ultimate_check.c \
		  $(SRCS_PR_DIR)/parameter_expansion.c \
		  $(SRCS_PR_DIR)/do_symbols.c \
		  $(SRCS_PR_DIR)/heredoc_parser.c \
		  $(SRCS_PR_DIR)/seperatos_parse.c \
		  $(SRCS_PR_DIR)/error.c \
		  $(SRCS_PR_DIR)/alias_parser.c \
		  $(SRCS_PR_DIR)/free_alias.c \
		  $(SRCS_PR_DIR)/readline_subshell.c \
		  $(SRCS_PR_DIR)/subshell_parser.c \
		  $(SRCS_PR_DIR)/ignore_quote.c


OBJECT_RL = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_RL:.c=.o)))
OBJECT_AC = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_AC:.c=.o)))
OBJECT_GL = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_GL:.c=.o)))
OBJECT_SH = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_SH:.c=.o)))
OBJECT_JB = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_JB:.c=.o)))
OBJECT_CH = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_CH:.c=.o)))
OBJECT_PR = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_PR:.c=.o)))
OBJECT_HA = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_HA:.c=.o)))
OBJECT_HI = $(patsubst %, $(OBJS_DIR)/%, $(notdir $(SRCS_HI:.c=.o)))

CC = gcc 
CFLAGS = -Wextra -Werror -Wall

BoldRed = \033[1;31m
BoldGreen = \033[1;32m
BoldBlue = \033[1;34m
BoldYellow = \033[01;33m
ED = \033[0m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJECT_RL) $(OBJECT_AC) $(OBJECT_HI) $(OBJECT_GL) $(OBJECT_SH) $(OBJECT_JB) $(OBJECT_CH) $(OBJECT_PR) $(OBJECT_HA)
	@make -C libft/
	@echo "$(BoldBlue)Linking...$(ED)"
	@$(CC) $(OBJECT_RL) $(OBJECT_AC) $(OBJECT_HI) $(OBJECT_GL) $(OBJECT_SH) $(OBJECT_JB) $(OBJECT_CH) $(OBJECT_PR) $(OBJECT_HA) $(LIBS_DIR) -o $(NAME)

	@echo "\033[1;31m ----------------\033[1;33m 🖥️\033[1;31m  ----------------  		 	 $(ED)";
	@echo "\033[1;31m|                                    |             $(ED)";
	@echo "\033[1;31m|   \033[1;33m⭐⭐⭐ \033[1;32m NMIL📀  W MANTI7📀 CH  \033[1;33m ⭐⭐⭐   \033[1;31m|     $(ED)";
	@echo "\033[1;31m|                                    |             ";
	@echo "\033[1;31m|      \033[1;00m   all rights reserved © 2020 \033[1;31m|             $(ED)";
	@echo "\033[1;31m ------------------------------------    		 	 $(ED)";
	@echo "\033[1;37m ------------------------------------    		 	 $(ED)";

 
$(OBJS_DIR) :
	@echo "$(BoldBlue)Creating Bins Folder...$(ED)"
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : $(SRCS_RL_DIR)/%.c
	@echo "$(BoldRed)Compiling Readline Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_RL_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_HI_DIR)/%.c
	@echo "$(BoldYellow)Compiling history Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_RL_DIR) -c $< -o $@


$(OBJS_DIR)/%.o : $(SRCS_GL_DIR)/%.c
	@echo "$(BoldGreen)Compiling globing Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_RL_DIR) -c $< -o $@


$(OBJS_DIR)/%.o : $(SRCS_AC_DIR)/%.c
	@echo "$(BoldYellow)Compiling shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_RL_DIR) -c $< -o $@


$(OBJS_DIR)/%.o : $(SRCS_SH_DIR)/%.c
	@echo "$(BoldYellow)Compiling shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_JB_DIR)/%.c
	@echo "$(BoldYellow)Compiling shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_CH_DIR)/%.c
	@echo "$(BoldYellow)Compiling shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_PR_DIR)/%.c
	@echo "$(BoldYellow)Compiling shell Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_HA_DIR)/%.c
	@echo "$(BoldYellow)Compiling hash Srcs...$(ED)"
	@$(CC) $(CFLAGS) $(INCS_SH_DIR) -c $< -o $@


clean:
	@echo "$(BoldRed)Remove Libft binaries...$(ED)"
	@make -C libft/ clean
	@echo "$(BoldRed)Remove Objs Folder...$(ED)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(BoldRed)Remove Libft Binaries & Static Library...$(ED)"
	@make -C libft/ fclean
	@echo "$(BoldRed)Remove Executable 42sh...$(ED)"
	@rm -f $(NAME)

help :
	@echo "SRCS_RL : $(SRCS_RL)"
	@echo "OBJECT_RL : $(OBJECT_RL)"
	@echo "\n"
	@echo "SRCS_SH : $(SRCS_SH)"
	@echo "OBJECT_SH : $(OBJECT_SH)"

re: fclean all
