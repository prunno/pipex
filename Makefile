CC=				cc
CFLAGS=			-Wall -Wextra
RM=				rm -f

NAME=			pipex
BIN_DIR=		bin/
NAME:=			${addprefix ${BIN_DIR}, ${NAME}}

SRC=			main.c														\
				free_utils.c												\
				parse_args.c												\
				heredoc.c													\
				parent_utils.c												\
				child_utils.c												\
				
SRC_DIR=		src/

OBJ=			$(SRC:.c=.o)
OBJ_DIR=		build/
OBJ:=			${addprefix ${OBJ_DIR}, ${OBJ}}

INC=			include/

LIBFT=			lib/libft.a
LIB_DIR=		lib/
LIB=			-Llib -lft


all:			${NAME}

${NAME}:		${BIN_DIR} ${OBJ_DIR} ${LIB_DIR} ${LIBFT} ${OBJ}
				${CC} ${CFLAGS} -O2 -I${INC} -o ${NAME} ${OBJ} ${LIB}

${LIB_DIR}:
				mkdir ${LIB_DIR}

${LIBFT}:
				+make -C libft
				cp libft/bin/libft.a ${LIBFT}

bonus:			all

${BIN_DIR}:
				mkdir bin

${OBJ_DIR}:
				mkdir build

clean:
				${RM} ${OBJ}
				+make -C libft clean

fclean:			clean
				${RM} ${NAME}
				${RM} ${LIBFT}
				+make -C libft fclean

re:				fclean all

%.o:			../${SRC_DIR}%.c
				${CC} ${CFLAGS} -I${INC} -c -o $@ $<

.PHONY:			all bonus clean fclean re
