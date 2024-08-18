import re
import argparse

def extract_globals_and_functions(c_file_content):
    # Regular expressions to match global variable declarations and function prototypes
    global_var_pattern = re.compile(
        r'^\s*(?:static\s+)?(?:extern\s+)?([\w\s\*]+)\s+([\w\s\*]+)\s*(?:=\s*[^;]*)?\s*;\s*$',
        re.MULTILINE
    )
    
    # Match function prototypes, including `static inline`
    func_pattern = re.compile(
        r'^\s*(static\s+inline\s+)?([\w\s\*]+)\s+(\w+)\s*\(([^)]*)\)\s*(?:\{[^}]*\}|\;)?',
        re.MULTILINE | re.DOTALL
    )

    # Match user-defined types: typedefs, structs, and enums
    typedef_pattern = re.compile(
        r'^\s*typedef\s+(\w[\w\s\*]+)\s+(\w+)\s*(?:=\s*[^;]*)?\s*;\s*$',
        re.MULTILINE
    )

    struct_enum_pattern = re.compile(
        r'^\s*(?:typedef\s+)?(?:struct|enum)\s+(\w+)?\s*\{([^}]*)\}\s*(\w+)?\s*(?:=\s*[^;]*)?\s*;\s*$',
        re.MULTILINE | re.DOTALL
    )

    global_vars = global_var_pattern.findall(c_file_content)
    functions = func_pattern.findall(c_file_content)
    typedefs = typedef_pattern.findall(c_file_content)
    structs_enums = struct_enum_pattern.findall(c_file_content)

    # Extract variable names and function prototypes
    global_vars_declaration = [
        (var[0].strip(), var[1].split(',')[0].strip()) for var in global_vars
    ]
    func_prototypes = [
        (func[1].strip(), func[2].strip(), func[3].strip()) for func in functions
    ]
    user_defined_types = typedefs + structs_enums

    return global_vars_declaration, func_prototypes, user_defined_types

def generate_struct(global_vars, functions, user_defined_types):
    struct_template = """
typedef struct {
    // Global Variables
    // Add global variables here

    // Function Pointers
    // Add function pointers here
    void (*Constructor)();

} GlobalState;
"""

    # Format global variables declarations
    global_vars_declaration = "\n    ".join(f"{data_type} {name};" for data_type, name in global_vars)
    
    # Format function pointers declarations
    function_pointers_declaration = "\n    ".join(f"{return_type} (*{name})({args});" for return_type, name, args in functions)

    # Format user-defined types declarations
    user_defined_types_declaration = "\n    ".join(
        f"{type_name} {name};" for type_name, _, name in user_defined_types
    )
    
    # Populate the template
    struct_definition = struct_template.replace(
        "// Global Variables\n    // Add global variables here", 
        global_vars_declaration + user_defined_types_declaration
    )
    struct_definition = struct_definition.replace(
        "// Function Pointers\n    // Add function pointers here", 
        function_pointers_declaration
    )

    return struct_definition

def generate_constructor(global_vars, functions, user_defined_types):
    constructor_template = """
void Constructor(GlobalState* state) {
    // Initialize global variables
    // Add initializations here
    // Example: state->variable = value;

    // Assign function pointers
    // Add function pointer assignments here
    // Example: state->function = function_name;

    // Set Constructor function pointer to itself
    state->Constructor = Constructor;
}
"""

    # Format global variables initializations
    global_vars_initialization = "\n    ".join(f"    state->{name} = /* initialize */;" for _, name in global_vars)
    
    # Format function pointer assignments
    function_pointers_assignment = "\n    ".join(f"    state->{name} = {name};" for _, name, _ in functions)

    # Populate the constructor template
    constructor_definition = constructor_template.replace(
        "// Initialize global variables\n    // Add initializations here", 
        global_vars_initialization
    )
    constructor_definition = constructor_definition.replace(
        "// Assign function pointers\n    // Add function pointer assignments here", 
        function_pointers_assignment
    )

    return constructor_definition

def main(c_file_path):
    with open(c_file_path, 'r') as file:
        c_file_content = file.read()

    global_vars, functions, user_defined_types = extract_globals_and_functions(c_file_content)
    struct_definition = generate_struct(global_vars, functions, user_defined_types)
    constructor_definition = generate_constructor(global_vars, functions, user_defined_types)

    with open(c_file_path, 'a') as file:
        file.write(struct_definition + '\n\n' + constructor_definition)

    print(f"Struct definition and Constructor written to {c_file_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Convert a C file into a C struct with global variables, function pointers, and a Constructor function.')
    parser.add_argument('c_file', help='The C file to parse')
    args = parser.parse_args()

    main(args.c_file)
