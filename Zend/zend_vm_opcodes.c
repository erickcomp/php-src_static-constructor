/*
   +----------------------------------------------------------------------+
   | Zend Engine                                                          |
   +----------------------------------------------------------------------+
   | Copyright (c) Zend Technologies Ltd. (http://www.zend.com)           |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
   | Authors: Andi Gutmans <andi@php.net>                                 |
   |          Zeev Suraski <zeev@php.net>                                 |
   |          Dmitry Stogov <dmitry@php.net>                              |
   +----------------------------------------------------------------------+
*/

#include <stdio.h>
#include <zend.h>
#include <zend_vm_opcodes.h>

static const char *zend_vm_opcodes_names[203] = {
	"ZEND_NOP",
	"ZEND_ADD",
	"ZEND_SUB",
	"ZEND_MUL",
	"ZEND_DIV",
	"ZEND_MOD",
	"ZEND_SL",
	"ZEND_SR",
	"ZEND_CONCAT",
	"ZEND_BW_OR",
	"ZEND_BW_AND",
	"ZEND_BW_XOR",
	"ZEND_POW",
	"ZEND_BW_NOT",
	"ZEND_BOOL_NOT",
	"ZEND_BOOL_XOR",
	"ZEND_IS_IDENTICAL",
	"ZEND_IS_NOT_IDENTICAL",
	"ZEND_IS_EQUAL",
	"ZEND_IS_NOT_EQUAL",
	"ZEND_IS_SMALLER",
	"ZEND_IS_SMALLER_OR_EQUAL",
	"ZEND_ASSIGN",
	"ZEND_ASSIGN_DIM",
	"ZEND_ASSIGN_OBJ",
	"ZEND_ASSIGN_STATIC_PROP",
	"ZEND_ASSIGN_OP",
	"ZEND_ASSIGN_DIM_OP",
	"ZEND_ASSIGN_OBJ_OP",
	"ZEND_ASSIGN_STATIC_PROP_OP",
	"ZEND_ASSIGN_REF",
	"ZEND_QM_ASSIGN",
	"ZEND_ASSIGN_OBJ_REF",
	"ZEND_ASSIGN_STATIC_PROP_REF",
	"ZEND_PRE_INC",
	"ZEND_PRE_DEC",
	"ZEND_POST_INC",
	"ZEND_POST_DEC",
	"ZEND_PRE_INC_STATIC_PROP",
	"ZEND_PRE_DEC_STATIC_PROP",
	"ZEND_POST_INC_STATIC_PROP",
	"ZEND_POST_DEC_STATIC_PROP",
	"ZEND_JMP",
	"ZEND_JMPZ",
	"ZEND_JMPNZ",
	NULL,
	"ZEND_JMPZ_EX",
	"ZEND_JMPNZ_EX",
	"ZEND_CASE",
	"ZEND_CHECK_VAR",
	"ZEND_SEND_VAR_NO_REF_EX",
	"ZEND_CAST",
	"ZEND_BOOL",
	"ZEND_FAST_CONCAT",
	"ZEND_ROPE_INIT",
	"ZEND_ROPE_ADD",
	"ZEND_ROPE_END",
	"ZEND_BEGIN_SILENCE",
	"ZEND_END_SILENCE",
	"ZEND_INIT_FCALL_BY_NAME",
	"ZEND_DO_FCALL",
	"ZEND_INIT_FCALL",
	"ZEND_RETURN",
	"ZEND_RECV",
	"ZEND_RECV_INIT",
	"ZEND_SEND_VAL",
	"ZEND_SEND_VAR_EX",
	"ZEND_SEND_REF",
	"ZEND_NEW",
	"ZEND_INIT_NS_FCALL_BY_NAME",
	"ZEND_FREE",
	"ZEND_INIT_ARRAY",
	"ZEND_ADD_ARRAY_ELEMENT",
	"ZEND_INCLUDE_OR_EVAL",
	"ZEND_UNSET_VAR",
	"ZEND_UNSET_DIM",
	"ZEND_UNSET_OBJ",
	"ZEND_FE_RESET_R",
	"ZEND_FE_FETCH_R",
	"ZEND_EXIT",
	"ZEND_FETCH_R",
	"ZEND_FETCH_DIM_R",
	"ZEND_FETCH_OBJ_R",
	"ZEND_FETCH_W",
	"ZEND_FETCH_DIM_W",
	"ZEND_FETCH_OBJ_W",
	"ZEND_FETCH_RW",
	"ZEND_FETCH_DIM_RW",
	"ZEND_FETCH_OBJ_RW",
	"ZEND_FETCH_IS",
	"ZEND_FETCH_DIM_IS",
	"ZEND_FETCH_OBJ_IS",
	"ZEND_FETCH_FUNC_ARG",
	"ZEND_FETCH_DIM_FUNC_ARG",
	"ZEND_FETCH_OBJ_FUNC_ARG",
	"ZEND_FETCH_UNSET",
	"ZEND_FETCH_DIM_UNSET",
	"ZEND_FETCH_OBJ_UNSET",
	"ZEND_FETCH_LIST_R",
	"ZEND_FETCH_CONSTANT",
	"ZEND_CHECK_FUNC_ARG",
	"ZEND_EXT_STMT",
	"ZEND_EXT_FCALL_BEGIN",
	"ZEND_EXT_FCALL_END",
	"ZEND_EXT_NOP",
	"ZEND_TICKS",
	"ZEND_SEND_VAR_NO_REF",
	"ZEND_CATCH",
	"ZEND_THROW",
	"ZEND_FETCH_CLASS",
	"ZEND_CLONE",
	"ZEND_RETURN_BY_REF",
	"ZEND_INIT_METHOD_CALL",
	"ZEND_INIT_STATIC_METHOD_CALL",
	"ZEND_ISSET_ISEMPTY_VAR",
	"ZEND_ISSET_ISEMPTY_DIM_OBJ",
	"ZEND_SEND_VAL_EX",
	"ZEND_SEND_VAR",
	"ZEND_INIT_USER_CALL",
	"ZEND_SEND_ARRAY",
	"ZEND_SEND_USER",
	"ZEND_STRLEN",
	"ZEND_DEFINED",
	"ZEND_TYPE_CHECK",
	"ZEND_VERIFY_RETURN_TYPE",
	"ZEND_FE_RESET_RW",
	"ZEND_FE_FETCH_RW",
	"ZEND_FE_FREE",
	"ZEND_INIT_DYNAMIC_CALL",
	"ZEND_DO_ICALL",
	"ZEND_DO_UCALL",
	"ZEND_DO_FCALL_BY_NAME",
	"ZEND_PRE_INC_OBJ",
	"ZEND_PRE_DEC_OBJ",
	"ZEND_POST_INC_OBJ",
	"ZEND_POST_DEC_OBJ",
	"ZEND_ECHO",
	"ZEND_OP_DATA",
	"ZEND_INSTANCEOF",
	"ZEND_GENERATOR_CREATE",
	"ZEND_MAKE_REF",
	"ZEND_DECLARE_FUNCTION",
	"ZEND_DECLARE_LAMBDA_FUNCTION",
	"ZEND_DECLARE_CONST",
	"ZEND_DECLARE_CLASS",
	"ZEND_DECLARE_CLASS_DELAYED",
	"ZEND_DECLARE_ANON_CLASS",
	"ZEND_ADD_ARRAY_UNPACK",
	"ZEND_ISSET_ISEMPTY_PROP_OBJ",
	"ZEND_HANDLE_EXCEPTION",
	"ZEND_USER_OPCODE",
	"ZEND_ASSERT_CHECK",
	"ZEND_JMP_SET",
	"ZEND_UNSET_CV",
	"ZEND_ISSET_ISEMPTY_CV",
	"ZEND_FETCH_LIST_W",
	"ZEND_SEPARATE",
	"ZEND_FETCH_CLASS_NAME",
	"ZEND_CALL_TRAMPOLINE",
	"ZEND_DISCARD_EXCEPTION",
	"ZEND_YIELD",
	"ZEND_GENERATOR_RETURN",
	"ZEND_FAST_CALL",
	"ZEND_FAST_RET",
	"ZEND_RECV_VARIADIC",
	"ZEND_SEND_UNPACK",
	"ZEND_YIELD_FROM",
	"ZEND_COPY_TMP",
	"ZEND_BIND_GLOBAL",
	"ZEND_COALESCE",
	"ZEND_SPACESHIP",
	"ZEND_FUNC_NUM_ARGS",
	"ZEND_FUNC_GET_ARGS",
	"ZEND_FETCH_STATIC_PROP_R",
	"ZEND_FETCH_STATIC_PROP_W",
	"ZEND_FETCH_STATIC_PROP_RW",
	"ZEND_FETCH_STATIC_PROP_IS",
	"ZEND_FETCH_STATIC_PROP_FUNC_ARG",
	"ZEND_FETCH_STATIC_PROP_UNSET",
	"ZEND_UNSET_STATIC_PROP",
	"ZEND_ISSET_ISEMPTY_STATIC_PROP",
	"ZEND_FETCH_CLASS_CONSTANT",
	"ZEND_BIND_LEXICAL",
	"ZEND_BIND_STATIC",
	"ZEND_FETCH_THIS",
	"ZEND_SEND_FUNC_ARG",
	"ZEND_ISSET_ISEMPTY_THIS",
	"ZEND_SWITCH_LONG",
	"ZEND_SWITCH_STRING",
	"ZEND_IN_ARRAY",
	"ZEND_COUNT",
	"ZEND_GET_CLASS",
	"ZEND_GET_CALLED_CLASS",
	"ZEND_GET_TYPE",
	"ZEND_ARRAY_KEY_EXISTS",
	"ZEND_MATCH",
	"ZEND_CASE_STRICT",
	"ZEND_MATCH_ERROR",
	"ZEND_JMP_NULL",
	"ZEND_CHECK_UNDEF_ARGS",
	"ZEND_FETCH_GLOBALS",
	"ZEND_VERIFY_NEVER_TYPE",
	"ZEND_CALLABLE_CONVERT",
};

static uint32_t zend_vm_opcodes_flags[203] = {
	0x00000000,
	0x00000b0b,
	0x00000b0b,
	0x80000b0b,
	0x00000707,
	0x00000b0b,
	0x00000b0b,
	0x00000b0b,
	0x40000707,
	0x80000b0b,
	0x80000b0b,
	0x80000b0b,
	0x00000707,
	0x0000000b,
	0x00000007,
	0x80000707,
	0x80000303,
	0x80000303,
	0x80000707,
	0x80000707,
	0x00000b0b,
	0x00000b0b,
	0x00000301,
	0x00006701,
	0x00040751,
	0x00040000,
	0x04000701,
	0x04006701,
	0x04000751,
	0x04000000,
	0x0b000101,
	0x00000003,
	0x0b040751,
	0x0b040000,
	0x00000001,
	0x00000001,
	0x00000001,
	0x00000001,
	0x00040000,
	0x00040000,
	0x00040000,
	0x00040000,
	0x00000020,
	0x00002007,
	0x00002007,
	0x00000000,
	0x00002007,
	0x00002007,
	0x00000705,
	0x00000101,
	0x00001301,
	0x07000003,
	0x00000007,
	0x00000707,
	0x01000701,
	0x01000701,
	0x01000701,
	0x00000000,
	0x00000001,
	0x01040300,
	0x00000000,
	0x01040310,
	0x00000003,
	0x00040110,
	0x00040310,
	0x00001307,
	0x00001301,
	0x00001301,
	0x0100a173,
	0x01040300,
	0x00000005,
	0x00186703,
	0x00106703,
	0x08000007,
	0x00010107,
	0x00000701,
	0x00040751,
	0x00002003,
	0x03000001,
	0x00000000,
	0x00010107,
	0x00000707,
	0x00040757,
	0x00010107,
	0x00006701,
	0x00640751,
	0x00010107,
	0x00006701,
	0x00040751,
	0x00010107,
	0x00000707,
	0x00040757,
	0x00010107,
	0x00006703,
	0x00240753,
	0x00010107,
	0x00000701,
	0x00040751,
	0x0000070b,
	0x00040391,
	0x00001301,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x01000000,
	0x00001301,
	0x02042003,
	0x00000007,
	0x00040771,
	0x00000057,
	0x0b000003,
	0x01040757,
	0x01048773,
	0x00030107,
	0x00020707,
	0x00001303,
	0x00001301,
	0x01000703,
	0x01000000,
	0x00001003,
	0x00000007,
	0x00040003,
	0x09000007,
	0x0000a103,
	0x00002003,
	0x03000001,
	0x00000005,
	0x01000700,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00040751,
	0x00040751,
	0x00040751,
	0x00040751,
	0x00000007,
	0x00000000,
	0x00047305,
	0x00000000,
	0x00000101,
	0x00001000,
	0x00001003,
	0x00000303,
	0x00000003,
	0x00000303,
	0x00040000,
	0x00000000,
	0x00060757,
	0x00000000,
	0x00000000,
	0x00002000,
	0x00002003,
	0x00000101,
	0x00020101,
	0x00000701,
	0x00000101,
	0x00000075,
	0x00000000,
	0x00000000,
	0x0b000703,
	0x00000003,
	0x00000020,
	0x00003000,
	0x00040110,
	0x00000000,
	0x00000007,
	0x00000105,
	0x00040301,
	0x00002003,
	0x00000707,
	0x00000101,
	0x00000103,
	0x00047000,
	0x00647000,
	0x00047000,
	0x00047000,
	0x00247000,
	0x00047000,
	0x00040000,
	0x00067000,
	0x00040b73,
	0x00100101,
	0x00100101,
	0x00000101,
	0x00001301,
	0x00000101,
	0x0300030b,
	0x0300030b,
	0x01000303,
	0x00000107,
	0x00000107,
	0x00000101,
	0x00000103,
	0x00000707,
	0x0300030b,
	0x00000301,
	0x0000010b,
	0x00002003,
	0x00000101,
	0x00000101,
	0x00000101,
	0x00000101,
};

ZEND_API const char* ZEND_FASTCALL zend_get_opcode_name(zend_uchar opcode) {
	if (UNEXPECTED(opcode > ZEND_VM_LAST_OPCODE)) {
		return NULL;
	}
	return zend_vm_opcodes_names[opcode];
}
ZEND_API uint32_t ZEND_FASTCALL zend_get_opcode_flags(zend_uchar opcode) {
	if (UNEXPECTED(opcode > ZEND_VM_LAST_OPCODE)) {
		opcode = ZEND_NOP;
	}
	return zend_vm_opcodes_flags[opcode];
}
ZEND_API zend_uchar zend_get_opcode_id(const char *name, size_t length) {
	zend_uchar opcode;
	for (opcode = 0; opcode < (sizeof(zend_vm_opcodes_names) / sizeof(zend_vm_opcodes_names[0])) - 1; opcode++) {
		const char *opcode_name = zend_vm_opcodes_names[opcode];
		if (opcode_name && strncmp(opcode_name, name, length) == 0) {
			return opcode;
		}
	}
	return ZEND_VM_LAST_OPCODE + 1;
}
