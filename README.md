# Compiler1.2
FreeC++ IDE 的开发。
目标：做成一个自由开源的C/C++集成开发工具。最重要的是要轻便，调试功能要强大（最好要有CodeBlocks的轻便，VS的强大的调试工具）。


A.2.1 Expressions
(6.5.1)primary-expression:
		identifier
        constant
        string-literal
        ( expression )

(6.5.2)postfix-expression:
        primary-expression{[ expression ]}
		primary-expression{( argument-expression-list_opt )}
		primary-expression{. identifier}
		primary-expression{-> identifier}
		primary-expression{++}
		primary-expression{--}
		primary-expression{-> identifier}

		( type-name ) { initializer-list }  {[ expression ]}
		( type-name ) { initializer-list }  {( argument-expression-list_opt )}
		( type-name ) { initializer-list }  {. identifier}
		( type-name ) { initializer-list }  {-> identifier}
		( type-name ) { initializer-list }  {++}
		( type-name ) { initializer-list }  {--}
		( type-name ) { initializer-list }  {-> identifier}

		( type-name ) { initializer-list ,}  {[ expression ]}
		( type-name ) { initializer-list ,}  {( argument-expression-list_opt )}
		( type-name ) { initializer-list ,}  {. identifier}
		( type-name ) { initializer-list ,}  {-> identifier}
		( type-name ) { initializer-list ,}  {++}
		( type-name ) { initializer-list ,}  {--}
		( type-name ) { initializer-list ,}  {-> identifier}

(6.5.2) argument-expression-list:
		assignment-expression{, assignment-expression}
		
(6.5.3) unary-expression:
		postfix-expression
		++ unary-expression
		-- unary-expression
		unary-operator cast-expression
		sizeof unary-expression
		sizeof ( type-name )

(6.5.3) unary-operator: one of
		& * + - ~ !

(6.5.4) cast-expression:
		unary-expression
		( type-name ) cast-expression

(6.5.5) multiplicative-expression:
		cast-expression{ * cast-expression}
		cast-expression{ / cast-expression}
		cast-expression{ % cast-expression}

(6.5.6) additive-expression:
		multiplicative-expression{+ multiplicative-expression}
	    multiplicative-expression{- multiplicative-expression}

(6.5.7) shift-expression:
		additive-expression{<< additive-expression}
		additive-expression{>> additive-expression}

(6.5.8) relational-expression:
		shift-expression{< shift-expression}
	    shift-expression{> shift-expression}
		shift-expression{<= shift-expression}
		shift-expression{<= shift-expression}

(6.5.9) equality-expression:
		relational-expression{== relational-expression}
		relational-expression{!= relational-expression}

(6.5.10) AND-expression:
		equality-expression{& equality-expression}
		
(6.5.11) exclusive-OR-expression:
		AND-expression{^ AND-expression}
		
(6.5.12) inclusive-OR-expression:
		exclusive-OR-expression{| exclusive-OR-expression}
		
(6.5.13) logical-AND-expression:
		inclusive-OR-expression{&& inclusive-OR-expression}
		
(6.5.14) logical-OR-expression:
		logical-AND-expression{|| logical-AND-expression}
		
(6.5.15) conditional-expression:
		logical-OR-expression
		logical-OR-expression ? expression : conditional-expression
		
(6.5.16) assignment-expression:
		conditional-expression
		unary-expression assignment-operator assignment-expression

(6.5.16) assignment-operator: one of
		= *= /= %= += -= <<= >>= &= ^= |=

(6.5.17) expression:
		assignment-expression{, assignment-expression}

(6.6) constant-expression:
		conditional-expression


A.2.4 External definitions
(6.9) translation-unit:
		external-declaration{external-declaration}

(6.9) external-declaration:
		function-definition
		declaration

(6.9.1) function-definition:
		declaration-specifiers declarator declaration-list_opt compound-statement

(6.9.1) declaration-list:
		declaration{declaration}


A.2.2 Declarations
(6.7) declaration:
		declaration-specifiers init-declarator-listopt ;

(6.7) declaration-specifiers:
		storage-class-specifier declaration-specifiers_opt
		type-specifier declaration-specifiers_opt
		type-qualifier declaration-specifiers_opt
		function-specifier declaration-specifiers_opt

(6.7) init-declarator-list:
		init-declarator
		init-declarator-list , init-declarator
(6.7) init-declarator:
		declarator
		declarator = initializer
(6.7.1) storage-class-specifier:
		typedef
		extern
		static
		auto
		register
(6.7.2) type-specifier:
		void
		char
		short
		int
		long
		float
		double
		signed
		unsigned
		_Bool
		_Complex
		_Imaginary
		struct-or-union-specifier
		enum-specifier
		typedef-name

(6.7.2.1) struct-or-union-specifier:
		struct-or-union identifier_opt { struct-declaration-list }
		struct-or-union identifier
(6.7.2.1) struct-or-union:
		struct
		union
(6.7.2.1) struct-declaration-list:
		struct-declaration
		struct-declaration-list struct-declaration
(6.7.2.1) struct-declaration:
		specifier-qualifier-list struct-declarator-list ;
(6.7.2.1) specifier-qualifier-list:
		type-specifier specifier-qualifier-listopt
		type-qualifier specifier-qualifier-listopt
(6.7.2.1) struct-declarator-list:
		struct-declarator
		struct-declarator-list , struct-declarator
(6.7.2.1) struct-declarator:
		declarator
		declarator_opt : constant-expression
(6.7.2.2) enum-specifier:
		enum identifieropt { enumerator-list }
		enum identifieropt { enumerator-list , }
		enum identifier
(6.7.2.2) enumerator-list:
		enumerator
		enumerator-list , enumerator
(6.7.2.2) enumerator:
		enumeration-constant
		enumeration-constant = constant-expression
(6.7.3) type-qualifier:
		const
		restrict
		volatile
(6.7.4) function-specifier:
		inline
(6.7.5) declarator:
		pointer_opt direct-declarator
(6.7.5) direct-declarator:
		identifier
		( declarator )
		direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
		direct-declarator [ static type-qualifier-listopt assignment-expression ]
		direct-declarator [ type-qualifier-list static assignment-expression ]
		direct-declarator [ type-qualifier-listopt * ]
		direct-declarator ( parameter-type-list )
		direct-declarator ( identifier-listopt )
(6.7.5) pointer:
		* type-qualifier-listopt
		* type-qualifier-listopt pointer
(6.7.5) type-qualifier-list:
		type-qualifier
		type-qualifier-list type-qualifier
(6.7.5) parameter-type-list:
		parameter-list
		parameter-list , ...
(6.7.5) parameter-list:
		parameter-declaration
		parameter-list , parameter-declaration
(6.7.5) parameter-declaration:
		declaration-specifiers declarator
		declaration-specifiers abstract-declaratoropt
(6.7.5) identifier-list:
		identifier
		identifier-list , identifier
(6.7.6) type-name:
		specifier-qualifier-list abstract-declaratoropt
(6.7.6) abstract-declarator:
		pointer
		pointeropt direct-abstract-declarator
(6.7.6) direct-abstract-declarator:
		( abstract-declarator )
		direct-abstract-declarator_opt [ assignment-expressionopt ]
		direct-abstract-declarator_opt [ * ]
		direct-abstract-declarator_opt ( parameter-type-listopt )
(6.7.7) typedef-name:
		identifier
(6.7.8) initializer:
		assignment-expression
		{ initializer-list }
		{ initializer-list , }
(6.7.8) initializer-list:
		designationopt initializer
		initializer-list , designationopt initializer
(6.7.8) designation:
		designator-list =
(6.7.8) designator-list:
		designator
		designator-list designator
(6.7.8) designator:
		[ constant-expression ]
		. identifier

A.2.3 Statements
(6.8) statement:
		labeled-statement
		compound-statement
		expression-statement
		selection-statement
		iteration-statement
		jump-statement

(6.8.1) labeled-statement:
		identifier : statement
		case constant-expression : statement
		default : statement
(6.8.2) compound-statement:
		{ block-item-listopt }
(6.8.2) block-item-list:
		block-item
		block-item-list block-item
(6.8.2) block-item:
		declaration
		statement
(6.8.3) expression-statement:
		expressionopt ;
(6.8.4) selection-statement:
		if ( expression ) statement
		if ( expression ) statement else statement
		switch ( expression ) statement
(6.8.5) iteration-statement:
		while ( expression ) statement
		do statement while ( expression ) ;
		for ( expressionopt ; expressionopt ; expressionopt ) statement
		for ( declaration expressionopt ; expressionopt ) statement
(6.8.6) jump-statement:
		goto identifier ;
		continue ;
		break ;
		return expressionopt ;