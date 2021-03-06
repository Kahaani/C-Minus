#ifndef SEMANTIC_AUX_H
#define SEMANTIC_AUX_H

typedef enum { Global_Var, Fun_Param, Compound_Var } StKind;

/******************************/

struct EntryDec;
typedef struct EntryDec * Entry;

struct EntryDec {
	char* name;
	Type type;
	int offset;
	StKind kind;
	
	Entry next;
};

/******************************/

struct SymtabDec;
typedef struct SymtabDec * Symtab;

struct SymtabDec {
	StKind kind;
	int size;
	Entry head;
	
	Symtab next;
};

/******************************/

struct FunInfoDec;
typedef struct FunInfoDec * FunInfo;

struct FunInfoDec {
	char* name;
	Type type;
	
	int param_size;
	int var_size;
	Symtab symtab; // point to Fun_Param
	
	int address; // for codegen module
	
	FunInfo next;
};

/******************************/

void push_funinfo(FunInfo funinfo);
FunInfo top_funinfo(void);
void reverse_fun_list(void);

void push_symtab(Symtab symtab);
void pop_symtab(void);
Symtab top_symtab(void);

Entry new_entry(char* name, Type type, int no, StKind kind, Entry next);
Symtab new_symtab(StKind kind);
FunInfo new_funinfo(char* name, Type type, Symtab symtab);

void insert_entry(char* name, Type type, int array_size, int lineno);
Entry lookup_entry(char* name);
FunInfo lookup_funinfo(char* name);

FunInfo prelude_input_funinfo(void);
FunInfo prelude_output_funinfo(void);

void print_symtab_root(Ast root);
void print_funlist(void);

#endif /* SEMANTIC_AUX_H */
