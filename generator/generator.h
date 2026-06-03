#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <shlwapi.h>



//                                                      ~  MACROS  ~
#define cast(T, x) ((T)(x))
#define deref(T, x) (*((T*)(x)))
#define CLASS_STRING
#define CLASS_STRING_BUILDER
#define CLASS_HTML
#define CLASS_UTIL
#define CLASS_TYPST
#define CLASS_CSS
#define CLASS_TS
#define CLASS_IO



//                                                      ~  CONSTANTS  ~
#define MAX_COMMAND 2048
#define BYTE 1
#define KILOBYTE (1024 * BYTE)
#define MEGABYTE (1024 * KILOBYTE)
#define PAGE_SIZE_LIMIT (200 * MEGABYTE)



//                                                  ~  TYPE DECLARATIONS  ~
typedef HANDLE File_Handle;
typedef HANDLE Pipe_Handle;
typedef HANDLE Process_Handle;
typedef enum File_Access {
	Read = GENERIC_READ,
	Write = GENERIC_WRITE } File_Access;
typedef struct String {
	char* buffer;
	uint32_t len; } String;
typedef uint32_t Range[2];
#define EMPTY_STRING (String){}
typedef struct String_Builder {
	char* pointer;
	String string;
	uint32_t cap; } String_Builder;
typedef struct Page {
	String name;
	String path;
	String_Builder string_builder; } Page;
typedef struct Style {
	String name;
	String path;
	String_Builder string_builder; } Style;
typedef struct Stack {
	void* buffer;
	void* top;
	uint32_t elem_size;
	void* end; } Stack;
typedef struct Generator {
	String executable_directory;
	String temp_path;
	String_Builder string_builder;
	Stack page_stack;
	Style* style; } Generator;
CLASS_HTML typedef struct Global_Attributes {
	String id;
	String class;
	String title; } Global_Attributes;
#define DEFAULT_GLOBAL_ATTRIBUTES (Global_Attributes){}
#define GLOBAL_ATTRIBUTES(...) (Global_Attributes){__VA_ARGS__}
CLASS_HTML typedef enum HTML_Element_Type {
	HTML_ELEMENT_A,
	HTML_ELEMENT_ABBR,
	HTML_ELEMENT_ADDRESS,
	HTML_ELEMENT_AREA,
	HTML_ELEMENT_ARTICLE,
	HTML_ELEMENT_ASIDE,
	HTML_ELEMENT_AUDIO,
	HTML_ELEMENT_B,
	HTML_ELEMENT_BASE,
	HTML_ELEMENT_BDI,
	HTML_ELEMENT_BDO,
	HTML_ELEMENT_BLOCKQUOTE,
	HTML_ELEMENT_BODY,
	HTML_ELEMENT_BR,
	HTML_ELEMENT_BUTTON,
	HTML_ELEMENT_CANVAS,
	HTML_ELEMENT_CAPTION,
	HTML_ELEMENT_CITE,
	HTML_ELEMENT_CODE,
	HTML_ELEMENT_COL,
	HTML_ELEMENT_COLGROUP,
	HTML_ELEMENT_DATA,
	HTML_ELEMENT_DATALIST,
	HTML_ELEMENT_DD,
	HTML_ELEMENT_DEL,
	HTML_ELEMENT_DETAILS,
	HTML_ELEMENT_DFN,
	HTML_ELEMENT_DIALOG,
	HTML_ELEMENT_DIV,
	HTML_ELEMENT_DL,
	HTML_ELEMENT_DOCTYPE,
	HTML_ELEMENT_DT,
	HTML_ELEMENT_EM,
	HTML_ELEMENT_EMBED,
	HTML_ELEMENT_FENCEDFRAME,
	HTML_ELEMENT_FIELDSET,
	HTML_ELEMENT_FIGCAPTION,
	HTML_ELEMENT_FIGURE,
	HTML_ELEMENT_FOOTER,
	HTML_ELEMENT_FORM,
	HTML_ELEMENT_HEAD,
	HTML_ELEMENT_HEADER,
	HTML_ELEMENT_H1,
	HTML_ELEMENT_H2,
	HTML_ELEMENT_H3,
	HTML_ELEMENT_H4,
	HTML_ELEMENT_H5,
	HTML_ELEMENT_H6,
	HTML_ELEMENT_HGROUP,
	HTML_ELEMENT_HR,
	HTML_ELEMENT_HTML,
	HTML_ELEMENT_I,
	HTML_ELEMENT_IFRAME,
	HTML_ELEMENT_IMG,
	HTML_ELEMENT_INPUT,
	HTML_ELEMENT_INS,
	HTML_ELEMENT_KBD,
	HTML_ELEMENT_LABEL,
	HTML_ELEMENT_LEGEND,
	HTML_ELEMENT_LI,
	HTML_ELEMENT_LINK,
	HTML_ELEMENT_MAIN,
	HTML_ELEMENT_MAP,
	HTML_ELEMENT_MARK,
	HTML_ELEMENT_MENU,
	HTML_ELEMENT_META,
	HTML_ELEMENT_METER,
	HTML_ELEMENT_NAV,
	HTML_ELEMENT_NOSCRIPT,
	HTML_ELEMENT_OBJECT,
	HTML_ELEMENT_OL,
	HTML_ELEMENT_OPTGROUP,
	HTML_ELEMENT_OPTION,
	HTML_ELEMENT_OUTPUT,
	HTML_ELEMENT_P,
	HTML_ELEMENT_PICTURE,
	HTML_ELEMENT_PRE,
	HTML_ELEMENT_PROGRESS,
	HTML_ELEMENT_Q,
	HTML_ELEMENT_RP,
	HTML_ELEMENT_RT,
	HTML_ELEMENT_RUBY,
	HTML_ELEMENT_S,
	HTML_ELEMENT_SAMP,
	HTML_ELEMENT_SCRIPT,
	HTML_ELEMENT_SEARCH,
	HTML_ELEMENT_SECTION,
	HTML_ELEMENT_SELECT,
	HTML_ELEMENT_SELECTEDCONTENT,
	HTML_ELEMENT_SLOT,
	HTML_ELEMENT_SMALL,
	HTML_ELEMENT_SOURCE,
	HTML_ELEMENT_SPAN,
	HTML_ELEMENT_STRONG,
	HTML_ELEMENT_STYLE,
	HTML_ELEMENT_SUB,
	HTML_ELEMENT_SUMMARY,
	HTML_ELEMENT_SUP,
	HTML_ELEMENT_TABLE,
	HTML_ELEMENT_TBODY,
	HTML_ELEMENT_TD,
	HTML_ELEMENT_TEMPLATE,
	HTML_ELEMENT_TEXTAREA,
	HTML_ELEMENT_TFOOT,
	HTML_ELEMENT_TH,
	HTML_ELEMENT_THEAD,
	HTML_ELEMENT_TIME,
	HTML_ELEMENT_TITLE,
	HTML_ELEMENT_TR,
	HTML_ELEMENT_TRACK,
	HTML_ELEMENT_U,
	HTML_ELEMENT_UL,
	HTML_ELEMENT_VAR,
	HTML_ELEMENT_VIDEO,
	HTML_ELEMENT_WBR,
	_HTML_ELEMENT_COUNT } HTML_Element_Type;

const char* HTML_ELEMENT_STRING[_HTML_ELEMENT_COUNT] = {
	"a",
	"abbr",
	"address",
	"area",
	"article",
	"aside",
	"audio",
	"b",
	"base",
	"bdi",
	"bdo",
	"blockquote",
	"body",
	"br",
	"button",
	"canvas",
	"caption",
	"cite",
	"code",
	"col",
	"colgroup",
	"data",
	"datalist",
	"dd",
	"del",
	"details",
	"dfn",
	"dialog",
	"div",
	"dl",
	"!DOCTYPE",
	"dt",
	"em",
	"embed",
	"fencedframe",
	"fieldset",
	"figcaption",
	"figure",
	"footer",
	"form",
	"head",
	"header",
	"h1",
	"h2",
	"h3",
	"h4",
	"h5",
	"h6",
	"hgroup",
	"hr",
	"html",
	"i",
	"iframe",
	"img",
	"input",
	"ins",
	"kbd",
	"label",
	"legend",
	"li",
	"link",
	"main",
	"map",
	"mark",
	"menu",
	"meta",
	"meter",
	"nav",
	"noscript",
	"object",
	"ol",
	"optgroup",
	"option",
	"output",
	"p",
	"picture",
	"pre",
	"progress",
	"q",
	"rp",
	"rt",
	"ruby",
	"s",
	"samp",
	"script",
	"search",
	"section",
	"select",
	"selectedcontent",
	"slot",
	"small",
	"source",
	"span",
	"strong",
	"style",
	"sub",
	"summary",
	"sup",
	"table",
	"tbody",
	"td",
	"template",
	"textarea",
	"tfoot",
	"th",
	"thead",
	"time",
	"title",
	"tr",
	"track",
	"u",
	"ul",
	"var",
	"video",
	"wbr" };

CLASS_HTML typedef enum HTML_Tag_Type {
	HTML_TAG_TYPE_OPEN,
	HTML_TAG_TYPE_EMPTY,
	HTML_TAG_TYPE_CLOSE } HTML_Tag_Type;
CLASS_HTML typedef enum HTML_Token_Type {
	HTML_TOKEN_TYPE_TAG,
	HTML_TOKEN_TYPE_CONTENT } HTML_Token_Type;
CLASS_HTML typedef struct HTML_Element HTML_Element; struct HTML_Element {
	HTML_Token_Type type;
	HTML_Tag_Type tag_type;
	HTML_Element_Type element_type;
	String open_tag_string;
	String content_string;
	String close_tag_string;
	HTML_Element* child;
	HTML_Element* sibling; };
CLASS_HTML typedef HTML_Element* HTML_File;
CLASS_HTML typedef struct HTML_Token HTML_Token; struct HTML_Token {
	Range range;
	HTML_Token_Type type;
	HTML_Tag_Type tag_type;
	HTML_Element_Type element_type;
	HTML_Token* child;
	HTML_Token* sibling;  };
// 1. Generate a tree of TAGs and CONTENTs (TOKENs).
// 2. Convert it to a tree of ELEMENTs.



//                                                ~  FORWARD DECLARATIONS  ~
CLASS_STRING static void string_determine_len(String* string);
CLASS_STRING static void string_trim_buffer_to_len(String* string);
CLASS_STRING static String string_from_buffer_and_len(char* buffer, uint32_t len);
CLASS_STRING static String string_from_buffer_and_range(char* buffer, Range range);
CLASS_STRING static String string_from_buffer(char* buffer);
CLASS_STRING static String string_from_len(uint32_t len);
CLASS_STRING static String string_from_file_handle(File_Handle handle);
CLASS_STRING static String string_from_file(String path);
CLASS_STRING static String string_slice_tail(String string, uint32_t start_index);
CLASS_STRING static String string_slice(String string, Range range);
CLASS_STRING static bool strings_equal(String string_a, String string_b);
CLASS_STRING static String strings_concatenate(String string_a, String string_b);
CLASS_STRING static bool string_contains(String string, char c);
CLASS_STRING static bool string_is_whitespace(String string);
CLASS_STRING static void string_to_file(String string, String path);
CLASS_STRING static String string_clone(String string);
#define STRING(x) string_from_buffer(x)
#define COMPTIME_STRING(x) { .buffer = x, .len = sizeof(x) - 1 }
static Stack new_stack(uint32_t count, size_t elem_size);
static void* stack_push(Stack* stack, void* elem);
static void* stack_peek(Stack* stack);
CLASS_STRING_BUILDER static String_Builder new_string_builder(uint32_t cap);
CLASS_STRING_BUILDER static void sbprints(String_Builder* sb, String string);
CLASS_STRING_BUILDER static void sbprints_times(String_Builder* sb, String string, uint32_t times);
CLASS_STRING_BUILDER static String string_builder_to_string(String_Builder* string_builder);
CLASS_IO static bool file_exists(String path);
CLASS_IO static File_Handle open_file(String path, File_Access access);
CLASS_IO static void create_file(String path);
CLASS_IO static void close_file(File_Handle handle);
CLASS_IO static File_Handle create_and_open_file(String path);
CLASS_IO static void remove_file(String path);
CLASS_IO static String get_executable_filepath();
CLASS_IO static String get_executable_directory();
CLASS_IO static bool exists_in_PATH(String name);
CLASS_IO static String path_join(String path_left, String path_right);
CLASS_IO static void create_directory(String path);
CLASS_IO static void remove_directory(String path);
CLASS_IO static void clear_directory(String path);
CLASS_IO static Process_Handle execute_command(String command, String working_directory, bool silence);
CLASS_IO static void wait_for_process(Process_Handle handle);
CLASS_IO static char* full_path_of(char* name);
CLASS_IO static void create_pipe(Pipe_Handle* write_handle, Pipe_Handle* read_handle, File_Access inherited, uint32_t size);
CLASS_IO static void destroy_pipe(Pipe_Handle handle);
CLASS_UTIL static char* _get_last_error();
CLASS_UTIL static void _sbprint_global_attributes(String_Builder* sb, Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_generic_element_begin(String type, Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_generic_element_end(String type);
CLASS_HTML static bool pgprint_html_element_begin(String language);
CLASS_HTML static bool pgprint_html_element_end();
CLASS_HTML static bool pgprint_head_element_begin(Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_head_element_end();
CLASS_HTML static bool pgprint_header_element_begin(Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_header_element_end();
CLASS_HTML static bool pgprint_nav_element_begin(Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_nav_element_end();
CLASS_HTML static bool pgprint_footer_element_begin(Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_footer_element_end();
CLASS_HTML static void _generic_element(String type, String content, Global_Attributes global_attributes);
CLASS_HTML static void pgprint_title_element(String content, Global_Attributes global_attributes);
CLASS_HTML static void pgprint_script_element(String source, bool async);
CLASS_HTML static void pgprint_img_element(String source);
CLASS_HTML static void pgprint_meta_charset_element();
CLASS_HTML static void pgprint_h1_element(String content, Global_Attributes global_attributes);
CLASS_HTML static void pgprint_h2_element(String content, Global_Attributes global_attributes);
CLASS_HTML static void pgprint_h3_element(String content, Global_Attributes global_attributes);
CLASS_HTML static void pgprint_h4_element(String content, Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_body_element_begin(Global_Attributes global_attributes);
CLASS_HTML static bool pgprint_body_element_end();
CLASS_HTML static void pgprint_link_stylesheet_element(String href);
CLASS_HTML static void pgprint_string(String string);
CLASS_HTML static bool pgprint_page_begin(String name);
CLASS_HTML static bool pgprint_page_end();
CLASS_HTML static bool html_element_type_must_be_empty(HTML_Element_Type element_type);
CLASS_HTML static void _debug_print_html_token(String content, HTML_Token* token);
CLASS_HTML static void _debug_print_html_token_recursive(String content, HTML_Token* token, uint32_t depth);
CLASS_HTML static HTML_Element_Type html_element_type_from_string(String string);
CLASS_HTML static HTML_File html_file_from_string(String content);
CLASS_HTML static HTML_File html_file_search_element_depth_first(HTML_File file, HTML_Element_Type element_type);
CLASS_HTML static HTML_File html_file_search_element_type(HTML_File file, HTML_Element_Type element_type);
CLASS_HTML static void html_token_correct_links(HTML_Token* token);
CLASS_HTML static HTML_Element* html_element_from_html_token_recursive(String content, HTML_Token* token);
CLASS_TYPST static HTML_File html_file_from_typst(String path);



//                                                       ~  GLOBALS  ~
// (TODO): Maybe this should be non-extern and the one in "build.c" should be extern.
Generator* generator;
const String INDENT_STRING = COMPTIME_STRING("  ");



//                                                        ~  STRING  ~
CLASS_STRING static void string_determine_len(String* string) {
	string->len = cast(uint32_t, strlen(string->buffer)); }
CLASS_STRING static void string_trim_buffer_to_len(String* string) {
	string->buffer = realloc(string->buffer, string->len + 1); }
CLASS_STRING static String string_from_buffer_and_len(char* buffer, uint32_t len) {
	return (String){ .buffer = buffer, .len = len }; }
CLASS_STRING static String string_from_buffer_and_range(char* buffer, Range range) {
	return (String){ .buffer = buffer + range[0], .len = range[1] - range[0] }; }
CLASS_STRING static String string_from_buffer(char* buffer) {
	return string_from_buffer_and_len(buffer, (uint32_t)strlen(buffer)); }
CLASS_STRING static String string_from_len(uint32_t len) {
	return (String){ .buffer = calloc(len + 1, 1), .len = len }; }
CLASS_STRING static String string_from_file_handle(File_Handle handle) {
	if (handle == INVALID_HANDLE_VALUE) { return EMPTY_STRING; }
	LARGE_INTEGER _file_size;
	GetFileSizeEx(handle, &_file_size);
	uint32_t file_size = cast(uint32_t, _file_size.QuadPart);
	String result = string_from_len(file_size);
	uint32_t bytes_read;
	ReadFile(handle, result.buffer, file_size, &bytes_read, NULL);
	result.len = cast(uint32_t, bytes_read);
	return result; }
CLASS_STRING static String string_from_file(String path) {
	File_Handle handle = open_file(path, Read);
	String result = string_from_file_handle(handle);
	close_file(handle);
	return result; }
CLASS_STRING static String string_slice_tail(String string, uint32_t start_index) {
	return (String){ .buffer = string.buffer + start_index, .len = string.len - start_index }; }
CLASS_STRING static String string_slice(String string, Range range) {
	return string_from_buffer_and_range(string.buffer, range); }
CLASS_STRING static bool strings_equal(String string_a, String string_b) {
	if (string_a.len != string_b.len) { return false; }
	for (uint32_t i = 0; i < string_a.len; i += 1) {
		if (string_a.buffer[i] != string_b.buffer[i]) { return false; } }
	return true; }
CLASS_STRING static String strings_concatenate(String string_a, String string_b) {
	String result;
	result.len = string_a.len + string_b.len;
	result.buffer = calloc(result.len, 1);
	strncpy(result.buffer, string_a.buffer, string_a.len);
	strncpy(result.buffer + string_a.len, string_b.buffer, string_b.len);
	return result; }
CLASS_STRING static bool string_contains(String string, char c) {
	for (uint32_t i = 0; i < string.len; i += 1) {
		if (string.buffer[i] == c) { return true; } }
	return false; }
CLASS_STRING static bool string_is_whitespace(String string) {
	String whitespace_characters = STRING("\t\n\v\f\r ");
	for (uint32_t i = 0; i < string.len; i += 1) {
		if (! string_contains(whitespace_characters, string.buffer[i])) {
			return false; } }
	return true; }
CLASS_STRING static void string_to_file(String string, String path) {
	DeleteFileA(path.buffer);
	File_Handle handle = create_and_open_file(path);
	assert(handle != INVALID_HANDLE_VALUE);
	assert(WriteFile(handle, string.buffer, string.len, NULL, NULL)); }
CLASS_STRING String string_clone(String string) {
	String clone = string_from_len(string.len);
	strncpy(clone.buffer, string.buffer, string.len);
	return clone; }
CLASS_STRING char* string_search_char(String string, char c) {
	for (uint32_t index = 0; index < string.len; index += 1) {
		if (string.buffer[index] == c) { return string.buffer + index; } }
	return 0; }
CLASS_STRING char* string_search_chars(String string, String chars) {
	for (uint32_t index = 0; index < string.len; index += 1) {
		if (string_contains(chars, string.buffer[index])) { return string.buffer + index; } }
	return 0; }



//                                                        ~  STACK  ~
static Stack new_stack(uint32_t count, size_t elem_size) {
	size_t cap = count * elem_size;
	void* buffer = calloc(cap, 1);
	void* end = (void*)((uintptr_t)buffer + cap);
	return (Stack){ .buffer = buffer, .top = buffer, .elem_size = (uint32_t)elem_size, .end = end }; }
static void* stack_push(Stack* stack, void* elem) {
	assert(stack != NULL);
	if (stack->top >= stack->end) { return NULL; }
	if (elem) { memcpy(stack->top, elem, stack->elem_size); }
	else { memset(stack->top, 0b0, stack->elem_size); }
	void* elem_ptr = stack->top;
	stack->top = cast(void*, cast(uintptr_t, stack->top) + stack->elem_size);
	return elem_ptr; }
static void* stack_peek(Stack* stack) {
	if (stack->top > stack->buffer) { return cast(void*, cast(uintptr_t, stack->top) - stack->elem_size); }
	else { return NULL; } }



//                                                    ~  STRING BUILDER  ~
CLASS_STRING_BUILDER static String_Builder new_string_builder(uint32_t cap) {
	char* buffer = calloc(cap, 1);
	return (String_Builder){ .pointer = buffer, .string = (String) { .buffer = buffer, .len = 0 }, .cap = cap }; }
CLASS_STRING_BUILDER static String string_builder_to_string(String_Builder* string_builder) {
	string_determine_len(&string_builder->string);
	string_trim_buffer_to_len(&string_builder->string);
	return string_builder->string; }
#define sbprintf(sb, ...) \
    ((sb)->pointer += sprintf((sb)->pointer, __VA_ARGS__))
CLASS_STRING_BUILDER static void sbprints(String_Builder* string_builder, String string) {
	sbprintf(string_builder, "%.*s", string.len, string.buffer); }
CLASS_STRING_BUILDER static void sbprints_times(String_Builder* string_builder, String string, uint32_t times) {
	for (uint32_t i = 0; i < times; i += 1) { sbprints(string_builder, string); } }



//                                                           ~  IO  ~
CLASS_IO static bool file_exists(String path) {
	return PathFindOnPathA(path.buffer, NULL); }
CLASS_IO static File_Handle open_file(String path, File_Access access) {
	File_Handle handle = CreateFileA(path.buffer, access, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return handle; }
CLASS_IO static void create_file(String path) {
	File_Handle file = CreateFileA(path.buffer, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(file); }
CLASS_IO static void close_file(File_Handle handle) {
	CloseHandle(handle); }
CLASS_IO static File_Handle create_and_open_file(String path) {
	File_Handle handle = CreateFileA(path.buffer, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	assert(handle != INVALID_HANDLE_VALUE);
	return handle; }
CLASS_IO static void remove_file(String path) {
	DeleteFileA(path.buffer); }
CLASS_IO static String get_executable_filepath() {
	String result = string_from_len(MAX_PATH);
	result.len = GetModuleFileNameA(NULL, result.buffer, MAX_PATH);
	string_trim_buffer_to_len(&result);
	return result; }
CLASS_IO static String get_executable_directory() {
	String path = get_executable_filepath();
	char* last_slash = strrchr(path.buffer, '\\');
	assert(last_slash != NULL);
	last_slash[0] = '\0';
	uint32_t n = cast(uint32_t, last_slash - path.buffer);
	String result = string_from_len(n);
	strncpy(result.buffer, path.buffer, n);
	return result; }
CLASS_IO static bool exists_in_PATH(String name) {
	char* buffer = calloc(MAX_PATH, 1);
	strncpy(buffer, name.buffer, MAX_PATH);
	return PathFindOnPathA(buffer, NULL); }
CLASS_IO static String path_join(String path_left, String path_right) {
	String result = string_from_len(MAX_PATH);
	PathCombineA(result.buffer, path_left.buffer, path_right.buffer);
	string_trim_buffer_to_len(&result);
	return result; }
CLASS_IO static void create_directory(String path) {
	CreateDirectoryA(path.buffer, NULL); }
CLASS_IO static void remove_directory(String path) {
	RemoveDirectoryA(path.buffer); }
CLASS_IO static void clear_directory(String path) {
	char* buffer = calloc(MAX_PATH, 1);
	sprintf(buffer, "%s\\*", path.buffer);
	WIN32_FIND_DATAA find_data = { };
	File_Handle handle = INVALID_HANDLE_VALUE;
	handle = FindFirstFileA(buffer, &find_data);
	assert(handle != INVALID_HANDLE_VALUE);
	do {
		if (find_data.cFileName[0] == '.') { continue; }
		String file_path = path_join(path, STRING(find_data.cFileName));
		remove_file(file_path); } while (FindNextFileA(handle, &find_data));
	FindClose(handle); }
CLASS_IO static Process_Handle execute_command(String command, String working_directory, bool silence) {
	Pipe_Handle write_handle = NULL;
	Pipe_Handle read_handle = NULL;
	create_pipe(&write_handle, &read_handle, Write, 10000);
	STARTUPINFOA startup_info = {
		.cb = sizeof(STARTUPINFOA),
		.dwFlags = STARTF_USESTDHANDLES,
		.hStdInput = INVALID_HANDLE_VALUE,
		.hStdOutput = write_handle,
		.hStdError = write_handle };
	PROCESS_INFORMATION process_info;
	bool ok = CreateProcessA(NULL, command.buffer, NULL, NULL, true, NORMAL_PRIORITY_CLASS, NULL, working_directory.buffer, &startup_info, &process_info);
	if (! ok) { printf("%s\n", _get_last_error()); }
	wait_for_process(process_info.hProcess);
	if (! silence) {
		String output = string_from_file_handle(read_handle);
		printf("%s\n", output.buffer); }
	destroy_pipe(write_handle);
	destroy_pipe(read_handle);
	return process_info.hProcess; }
CLASS_IO static void wait_for_process(Process_Handle handle) {
	WaitForSingleObject(handle, INFINITE); }
CLASS_IO static char* full_path_of(char* name) {
	char* buffer = calloc(MAX_PATH, 1);
	strcpy(buffer, name);
	PathFindOnPathA(buffer, NULL);
	return buffer; }
CLASS_IO static void create_pipe(Pipe_Handle* write_handle, Pipe_Handle* read_handle, File_Access inherited, uint32_t size) {
	SECURITY_ATTRIBUTES security_attributes = { .nLength = sizeof(SECURITY_ATTRIBUTES), .bInheritHandle = true, .lpSecurityDescriptor = NULL };
	assert(CreatePipe(cast(PHANDLE, read_handle), cast(PHANDLE, write_handle), &security_attributes, 0));
	assert(SetHandleInformation(((inherited == Read) ? deref(Pipe_Handle, write_handle) : deref(Pipe_Handle, read_handle)), HANDLE_FLAG_INHERIT, 0)); }
CLASS_IO static void destroy_pipe(Pipe_Handle handle) {
	CloseHandle(handle); }



//                                                        ~  UTIL  ~
CLASS_UTIL static char* _get_last_error() {
	char* message = NULL;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&message,
		0,
		NULL);
	return message; }
CLASS_UTIL static void _sbprint_global_attributes(String_Builder* sb, Global_Attributes global_attributes) {
	if (global_attributes.id.len > 0) { sbprintf(sb, "id=\"%s\" ", global_attributes.id.buffer); }
	if (global_attributes.class.len > 0) { sbprintf(sb, "class=\"%s\" ", global_attributes.class.buffer); }
	if (global_attributes.title.len > 0) { sbprintf(sb, "title=\"%s\" ", global_attributes.title.buffer); } }



//                                                        ~  HTML  ~
CLASS_HTML static bool pgprint_generic_element_begin(String type, Global_Attributes global_attributes) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<%s ", type.buffer);
	_sbprint_global_attributes(&page->string_builder, global_attributes);
	sbprintf(&page->string_builder, ">\n");
	return true; }
CLASS_HTML static bool pgprint_generic_element_end(String type) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "</%s>\n", type.buffer);
	return true; }
#define pgprint_generic_element_block(type, global_attributes) for (bool ok_ ## __LINE__ = pgprint_generic_element_begin(type, global_attributes); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_generic_element_end(type))
CLASS_HTML static bool pgprint_a_element_begin(String href, Global_Attributes global_attributes) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<a ");
	sbprintf(&page->string_builder, "href=\"%s\" ", href.buffer);
	_sbprint_global_attributes(&page->string_builder, global_attributes);
	sbprintf(&page->string_builder, ">\n");
	return true; }
CLASS_HTML static bool pgprint_a_element_end() {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "</a>\n");
	return true; }
#define pgprint_a_element_block(href, global_attributes) for (bool ok_ ## __LINE__ = pgprint_a_element_begin(href, global_attributes); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_a_element_end())
CLASS_HTML static bool pgprint_html_element_begin(String language) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<html lang=\"%s\">\n", language.buffer);
	return true; }
CLASS_HTML static bool pgprint_html_element_end() {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "</html>\n");
	return true; }
#define pgprint_html_element_block(language) for (bool ok_ ## __LINE__ = pgprint_html_element_begin(language); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_html_element_end())
CLASS_HTML static bool pgprint_head_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("head"), global_attributes); }
CLASS_HTML static bool pgprint_head_element_end() {
	return pgprint_generic_element_end(string_from_buffer("head")); }
#define pgprint_head_element_block(global_attributes) for (bool ok_ ## __LINE__ = pgprint_head_element_begin(global_attributes); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_head_element_end())
CLASS_HTML static bool pgprint_div_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("div"), global_attributes); }
CLASS_HTML static bool pgprint_div_element_end() {
	return pgprint_generic_element_end(string_from_buffer("div")); }
#define pgprint_div_element_block(global_attributes) for (bool ok_ ## __LINE__ = pgprint_div_element_begin(global_attributes); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_div_element_end())
CLASS_HTML static bool pgprint_header_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("header"), global_attributes); }
CLASS_HTML static bool pgprint_header_element_end() {
	return pgprint_generic_element_end(string_from_buffer("header")); }
#define pgprint_header_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("header"), global_attributes)
CLASS_HTML static bool pgprint_nav_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("nav"), global_attributes); }
CLASS_HTML static bool pgprint_nav_element_end() {
	return pgprint_generic_element_end(string_from_buffer("nav")); }
#define pgprint_nav_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("nav"), global_attributes)
CLASS_HTML static bool pgprint_footer_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("footer"), global_attributes); }
CLASS_HTML static bool pgprint_footer_element_end() {
	return pgprint_generic_element_end(string_from_buffer("footer")); }
#define pgprint_footer_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("footer"), global_attributes)
CLASS_HTML static bool pgprint_ul_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("ul"), global_attributes); }
CLASS_HTML static bool pgprint_ul_element_end() {
	return pgprint_generic_element_end(string_from_buffer("ul")); }
#define pgprint_ul_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("ul"), global_attributes)
CLASS_HTML static bool pgprint_li_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("li"), global_attributes); }
CLASS_HTML static bool pgprint_li_element_end() {
	return pgprint_generic_element_end(string_from_buffer("li")); }
#define pgprint_li_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("li"), global_attributes)
static void _generic_element(String type, String content, Global_Attributes global_attributes) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<%s ", type.buffer);
	_sbprint_global_attributes(&page->string_builder, global_attributes);
	sbprintf(&page->string_builder, ">%s</%s>\n", content.buffer, type.buffer); }
static void _generic_element_empty(String type) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<%s/>\n", type.buffer); }
CLASS_HTML static void pgprint_title_element(String content, Global_Attributes global_attributes) {
	_generic_element(string_from_buffer("title"), content, global_attributes); }
CLASS_HTML static void pgprint_script_element(String source, bool async) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<script ");
	if (async) { sbprintf(&page->string_builder, "async "); }
	if (source.len > 0) { sbprintf(&page->string_builder, "src=\"%s\"" , source.buffer); }
	sbprintf(&page->string_builder, "></script>\n"); }
CLASS_HTML static void pgprint_img_element(String source) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<img ");
	if (source.len > 0) { sbprintf(&page->string_builder, "src=\"%s\"" , source.buffer); }
	sbprintf(&page->string_builder, ">\n"); }
CLASS_HTML static void pgprint_meta_charset_element() {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<meta charset=\"utf-8\"/>\n"); }
CLASS_HTML static void pgprint_h1_element(String content, Global_Attributes global_attributes) {
	_generic_element(string_from_buffer("h1"), content, global_attributes); }
CLASS_HTML static void pgprint_h2_element(String content, Global_Attributes global_attributes) {
	_generic_element(string_from_buffer("h2"), content, global_attributes); }
CLASS_HTML static void pgprint_h3_element(String content, Global_Attributes global_attributes) {
	_generic_element(string_from_buffer("h3"), content, global_attributes); }
CLASS_HTML static void pgprint_h4_element(String content, Global_Attributes global_attributes) {
	_generic_element(string_from_buffer("h4"), content, global_attributes); }
CLASS_HTML static void pgprint_hr_element() {
	_generic_element_empty(STRING("hr")); }
CLASS_HTML static bool pgprint_body_element_begin(Global_Attributes global_attributes) {
	return pgprint_generic_element_begin(string_from_buffer("body"), global_attributes); }
CLASS_HTML static bool pgprint_body_element_end() {
	return pgprint_generic_element_end(string_from_buffer("body")); }
#define pgprint_body_element_block(global_attributes) pgprint_generic_element_block(string_from_buffer("body"), global_attributes)
CLASS_HTML static void pgprint_link_stylesheet_element(String href) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "<link href=\"%s\" rel=\"stylesheet\"/>\n", href.buffer); }
CLASS_HTML static void pgprint_string(String string) {
	Page* page = stack_peek(&generator->page_stack);
	sbprintf(&page->string_builder, "%s\n", string.buffer); }
CLASS_HTML static bool pgprint_page_begin(String name) {
	Page* page = stack_push(&generator->page_stack, NULL);
	page->name = name;
	String_Builder sb = new_string_builder(MAX_PATH);
	sbprintf(&sb, "%s.html", name.buffer);
	page->path = string_builder_to_string(&sb);
	page->string_builder = new_string_builder(PAGE_SIZE_LIMIT);
	sbprintf(&page->string_builder, "<!DOCTYPE html>\n");
	return true; }
CLASS_HTML static bool pgprint_page_end() {
	Page* page = stack_peek(&generator->page_stack);
	String content = string_builder_to_string(&page->string_builder);
	string_to_file(content, page->path);
	return true; }
#define pgprint_page_block(name) for (bool ok_ ## __LINE__ = pgprint_page_begin(name); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_page_end())
// (NOTE): This is necessary because there are certain types of elements which are allowed to be empty, but are also allowed to
// be closed with ">" instead of "/>".
CLASS_HTML static bool html_element_type_must_be_empty(HTML_Element_Type element_type) {
	switch (element_type) {
	case HTML_ELEMENT_AREA:
	case HTML_ELEMENT_BASE:
	case HTML_ELEMENT_BR:
	case HTML_ELEMENT_COL:
	case HTML_ELEMENT_DOCTYPE:
	case HTML_ELEMENT_EMBED:
	case HTML_ELEMENT_HR:
	case HTML_ELEMENT_IMG:
	case HTML_ELEMENT_LINK:
	case HTML_ELEMENT_META:
	case HTML_ELEMENT_SOURCE:
	case HTML_ELEMENT_TRACK: return true; }
	return false; }
CLASS_HTML static void _debug_print_html_token(String content, HTML_Token* token) {
	String token_string = string_clone(string_from_buffer_and_range(content.buffer, token->range));
	if (token->type == HTML_TOKEN_TYPE_CONTENT) {
		if (! string_is_whitespace(token_string)) {
			printf("\"%s\"\n", token_string.buffer); }
		else {
			printf("\" \"\n"); } }
	else {
		if (token->tag_type == HTML_TAG_TYPE_OPEN) {
			printf("<%s>\n", HTML_ELEMENT_STRING[token->element_type]); }
		else if (token->tag_type == HTML_TAG_TYPE_CLOSE) {
			printf("</%s>\n", HTML_ELEMENT_STRING[token->element_type]); }
		else if (token->tag_type == HTML_TAG_TYPE_EMPTY) {
			printf("<%s/>\n", HTML_ELEMENT_STRING[token->element_type]); } } }
CLASS_HTML static void _debug_print_html_token_recursive(String content, HTML_Token* token, uint32_t depth) {
	for (uint32_t i = 0; i < depth; i += 1) { printf("  "); }
	_debug_print_html_token(content, token);
	if (token->child != NULL) { _debug_print_html_token_recursive(content, token->child, depth + 1); }
	if (token->sibling != NULL) { _debug_print_html_token_recursive(content, token->sibling, depth); } }
CLASS_HTML static HTML_Element_Type html_element_type_from_string(String string) {
	for (uint32_t index = 0; index < _HTML_ELEMENT_COUNT; index += 1) {
		if (strings_equal(string, STRING(cast(char*, HTML_ELEMENT_STRING[index])))) {
			return cast(HTML_Element_Type, index); } }
	return -1; }
CLASS_HTML static HTML_File html_file_from_string(String content) {
	HTML_File file = {};
	uint32_t cursor = 0;
	HTML_Token* root_token = NULL;
	HTML_Token* last_token = NULL;
	while (true) {
		HTML_Token* token = calloc(1, sizeof(HTML_Token));
		if (root_token == NULL) { root_token = token; }
		if (last_token != NULL) { last_token->child = token; }
		if (content.buffer[cursor] == '<') {
			String typename_string = EMPTY_STRING;
			token->type = HTML_TOKEN_TYPE_TAG;
			token->range[0] = cursor;
			while (content.buffer[cursor] != '>') { cursor += 1; }
			token->range[1] = cursor + 1;
			cursor += 1;
			uint32_t typename_offset = 0;
			if (content.buffer[token->range[0] + 1] == '/') {
				token->tag_type = HTML_TAG_TYPE_CLOSE;
				typename_offset = 2; }
			else if (content.buffer[token->range[1] - 2] == '/') {
				token->tag_type = HTML_TAG_TYPE_EMPTY;
				typename_offset = 1; }
			else {
				token->tag_type = HTML_TAG_TYPE_OPEN;
				typename_offset = 1; }
			typename_string = string_slice_tail(content, token->range[0] + typename_offset);
			char* typename_end = string_search_chars(typename_string, STRING(" />"));
			if (typename_end != NULL) { typename_string.len = cast(uint32_t, typename_end - typename_string.buffer); }
			token->element_type = html_element_type_from_string(typename_string);
			if (html_element_type_must_be_empty(token->element_type)) {
				token->tag_type = HTML_TAG_TYPE_EMPTY; } }
		else {
			token->type = HTML_TOKEN_TYPE_CONTENT;
			token->range[0] = cursor;
			while ((content.buffer[cursor] != '<') && (cursor < content.len)) { cursor += 1; }
			token->range[1] = cursor; }
		last_token = token;
		if (cursor >= content.len - 1) { break; } }
	html_token_correct_links(root_token);
	// _debug_print_html_token_recursive(content, root_token, 0);
	file = html_element_from_html_token_recursive(content, root_token);
	return file; }
CLASS_HTML static HTML_File html_file_search_element_depth_first(HTML_File file, HTML_Element_Type element_type) {
	if (file == NULL) { return NULL; }
	if ((file->type == HTML_TOKEN_TYPE_TAG) && (file->element_type == element_type)) { return file; }
	HTML_File result = NULL;
	result = html_file_search_element_depth_first(file->child, element_type);
	if (result == NULL) {
		result = html_file_search_element_depth_first(file->sibling, element_type); }
	return result; }
CLASS_HTML static void sbprint_html_file_recursive(String_Builder* string_builder, HTML_File file, uint32_t depth) {
	if (file == NULL) { return; }
	if (file->type == HTML_TOKEN_TYPE_TAG) {
		sbprints(string_builder, file->open_tag_string);
		sbprint_html_file_recursive(string_builder, file->child, depth + 1);
		sbprints(string_builder, file->close_tag_string);
		sbprint_html_file_recursive(string_builder, file->sibling, depth);
	} else {
		sbprints(string_builder, file->content_string);
		sbprint_html_file_recursive(string_builder, file->sibling, depth); } }
CLASS_HTML static String html_file_to_string(HTML_File file) {
	HTML_Element* element = file;
	// Element stack. Before following "child" link, put element on the stack. //
	// Use string builder. //
	String_Builder string_builder = new_string_builder(PAGE_SIZE_LIMIT);
	// CLASS_HTML typedef struct HTML_Element {
	// 	HTML_Token_Type type;
	// 	HTML_Tag_Type tag_type;
	// 	HTML_Element_Type element_type;
	// 	String open_tag_string;
	// 	String content_string;
	// 	String close_tag_string;
	// 	void* child;
	// 	void* sibling; } HTML_Element;
	sbprint_html_file_recursive(&string_builder, file, 0);
	return string_builder_to_string(&string_builder); }
CLASS_HTML static void html_token_correct_links(HTML_Token* token) {
	if (token == NULL) { return; }
	if (token->type == HTML_TOKEN_TYPE_CONTENT) {
		if (token->child != NULL) {
			token->sibling = token->child;
			token->child = NULL;
			html_token_correct_links(token->sibling); } }
	else {
		if ((token->tag_type == HTML_TAG_TYPE_EMPTY) || (html_element_type_must_be_empty(token->element_type))) {
			if (token->child != NULL) {
				token->sibling = token->child;
				token->child = NULL;
				html_token_correct_links(token->sibling); } }
		else if (token->tag_type == HTML_TAG_TYPE_OPEN) {
			HTML_Token* closing_token_parent = NULL;
			HTML_Token* curr_token = token;
			while (true) {
				if (curr_token->child == NULL) { break; }
				HTML_Token* curr_token_child = cast(HTML_Token*, curr_token->child);
				if ((curr_token_child->type == HTML_TOKEN_TYPE_TAG) && (curr_token_child->element_type == token->element_type) && (curr_token_child->tag_type == HTML_TAG_TYPE_CLOSE)) {
					closing_token_parent = curr_token;
					// (NOTE): Is the first closing paren always the correct one?
					break; }
				curr_token = curr_token->child; }
			if (closing_token_parent == NULL) {
				if (token->child != NULL) {
					html_token_correct_links(token->child); } }
			else {
				HTML_Token* closing_token = closing_token_parent->child;
				token->sibling = closing_token;
				closing_token_parent->child = NULL;
				// if (closing_token->child != NULL) {
				// 	closing_token->sibling = closing_token->child;
				// 	closing_token->child = NULL; }
				html_token_correct_links(token->child);
				html_token_correct_links(token->sibling); } }
		else {
			if (token->child != NULL) {
				html_token_correct_links(token->child); } } }
	if (token->child) if ((token->type == HTML_TOKEN_TYPE_TAG) && (token->tag_type == HTML_TAG_TYPE_CLOSE)) {
		token->sibling = token->child;
		token->child = NULL; } }
CLASS_HTML static HTML_Element* html_element_from_html_token_recursive(String content, HTML_Token* token) {
	if (token == NULL) { return NULL; }
	HTML_Element* element = calloc(1, sizeof(HTML_Element));
	element->type = token->type;
	element->tag_type = token->tag_type;
	element->element_type = token->element_type;
	switch (token->type) {
	case HTML_TOKEN_TYPE_TAG:
		switch (token->tag_type) {
			case HTML_TAG_TYPE_OPEN:
				HTML_Token* close_tag = cast(HTML_Token*, token->sibling);
				assert(close_tag != NULL);
				element->open_tag_string = string_slice(content, token->range);
				element->close_tag_string = string_slice(content, close_tag->range);
				element->content_string = string_slice(content, (Range){ token->range[1], close_tag->range[0] });
				element->child = html_element_from_html_token_recursive(content, token->child);
				element->sibling = html_element_from_html_token_recursive(content, close_tag->sibling);  break;
			case HTML_TAG_TYPE_EMPTY:
				element->open_tag_string = string_slice(content, token->range);
				assert(element->child == NULL);
				element->sibling = html_element_from_html_token_recursive(content, token->sibling);
			break;
		} break;
	case HTML_TOKEN_TYPE_CONTENT:
		element->content_string = string_slice(content, token->range);
		element->child = html_element_from_html_token_recursive(content, token->child);
		element->sibling = html_element_from_html_token_recursive(content, token->sibling); break; }
	return element; }
// CLASS_HTML page_to_file(Page* page, String path) {
// // DICK
// }
// Page* page = stack_peek(&generator->page_stack);
// sbprintf(&page->string_builder, "<%s ", type.buffer);



//                                                         ~  CSS  ~
CLASS_CSS static bool pgprint_style_begin(String name) {
	Style* style = calloc(1, sizeof(Style));
	generator->style = style;
	style->name = name;
	String_Builder string_builder = new_string_builder(MAX_PATH);
	sbprintf(&string_builder, "%s.css", name.buffer);
	style->path = string_builder_to_string(&string_builder);
	style->string_builder = new_string_builder(1000000);
	// sbprintf(&style->string_builder, "html, body { font-family: \"Times New Roman\"; font-size: 18px; }\n");
	return true; }
CLASS_CSS static bool pgprint_style_end() {
	Style* style = generator->style;
	String content = string_builder_to_string(&style->string_builder);
	string_to_file(content, style->path);
	return true; }
#define pgprint_style_block(name) for (bool ok_ ## __LINE__ = pgprint_style_begin(name); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_style_end())
CLASS_CSS static bool pgprint_generic_rule_begin(String selector) {
	Style* style = generator->style;
	sbprintf(&style->string_builder, "%s {\n", selector.buffer);
	return true; }
CLASS_CSS static bool pgprint_generic_rule_end() {
	Style* style = generator->style;
	sbprintf(&style->string_builder, "}\n");
	return true; }
#define pgprint_generic_rule_block(selector) for (bool ok_ ## __LINE__ = pgprint_generic_rule_begin(selector); ok_ ## __LINE__; ok_ ## __LINE__ = ! pgprint_generic_rule_end())
CLASS_CSS static void pgprint_generic_declaration(String property, String value) {
	Style* style = generator->style;
	sbprintf(&style->string_builder, "%s%s: %s;\n", INDENT_STRING.buffer, property.buffer, value.buffer); }
CLASS_CSS static void pgprint_charset_atrule(String charset) {
	Style* style = generator->style;
	sbprintf(&style->string_builder, "@charset \"%s\";\n", charset.buffer); }
CLASS_CSS static void pgprint_font_face_atrule(String font_family, String src_url) {
	Style* style = generator->style;
	sbprintf(&style->string_builder, "@font-face {\n\tfont-family: \"%s\";\n\tsrc: url(\"%s\"); }\n", font_family.buffer, src_url.buffer); }
// DICK



static void begin(Generator* generator) {
	//--- CHECK PREREQUISITES ---//
	assert(exists_in_PATH(STRING("tsc")));
	assert(exists_in_PATH(STRING("typst.exe")));
	assert(exists_in_PATH(STRING("npm")));

	//--- INITIALIZE ENVIRONMENT ---//
	generator->executable_directory = get_executable_directory();
	generator->temp_path = path_join(generator->executable_directory, STRING("temp"));
	clear_directory(generator->temp_path);

	//--- INITIALIZE GENERATOR ---//
	// new_string_builder()
	generator->page_stack = new_stack(24, sizeof(Page));

	//--- CREATE FILES ---//
	// printf("Temp directory: %s\n", temp_path);

	// npm init ./temp --yes
	// execute_command("cmd.exe /c npm init --yes", temp_path);
	// execute_command("cmd.exe /c tsc --init", temp_path);
	const char* tsconfig_string =
		"{\n"
		"	\"compilerOptions\": {\n"
		"		\"target\": \"ES2024\",\n"
		"		\"outDir\": \"./dist\",\n"
		"		\"rootDir\": \"./src\",\n"
		"		\"module\": \"NodeNext\",\n"
		"		\"lib\": [ \"dom\", \"esnext\" ],\n"
		"		\"types\": [ \"@webgpu/types\" ],\n"
		"	}\n"
		"}\n";
	//--- CLEANUP ---//
	return; }



const char* TYPST_OUTPUT_NAME = "typst-out.html";
CLASS_TYPST static HTML_File html_file_from_typst(String path) {
	String_Builder command_sb = new_string_builder(MAX_COMMAND);
	String output_path = path_join(generator->temp_path, STRING(cast(char*, TYPST_OUTPUT_NAME)));
	sbprintf(&command_sb, "typst compile %s -f html --features html %s", path.buffer, output_path.buffer);
	String command = string_builder_to_string(&command_sb);
	Process_Handle typst_process = execute_command(command, generator->executable_directory, false);
	String output_string = string_from_file(output_path);
	remove_file(output_path);
	assert(! file_exists(output_path));
	// printf("%s\n", output_string.buffer);
	return html_file_from_string(output_string); }


