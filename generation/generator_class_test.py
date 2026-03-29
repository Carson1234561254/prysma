def generate_class_files():
    class_name = "MyClass"
    class_members = ["int x", "std::string name"]
    constructor_params = "int x, std::string name"
    methods = [
        "void doSomething();",
        "std::string getName();"
    ]

    # Générer le code pour le fichier .h
    class_code = f"""
#ifndef {class_name.upper()}_H
#define {class_name.upper()}_H

#include <string>

class {class_name} {{
private:
{''.join([f'    {member};\n' for member in class_members])}

public:
    {class_name}({constructor_params});
    ~{class_name}() = default;

{''.join([f'    {method}\n' for method in methods])}
}};

#endif
    """

    # Écrire le fichier .h
    class_filename = f"{class_name.lower()}.h"
    with open(class_filename, "w") as class_file:
        class_file.write(class_code)
    print(f"Fichier d'en-tête généré: {class_filename}")

    # Générer le code pour le fichier .cpp
    cpp_code = f"""
#include "{class_name.lower()}.h"

{class_name}::{class_name}({constructor_params}) {{
{''.join([f'    this->{member.split()[1]} = {member.split()[1]};\n' for member in class_members])}
}}

{''.join([f'{method} {{}}\n' for method in methods])}
    """

    # Écrire le fichier .cpp
    cpp_filename = f"{class_name.lower()}.cpp"
    with open(cpp_filename, "w") as cpp_file:
        cpp_file.write(cpp_code)
    print(f"Fichier source généré: {cpp_filename}")

# Appel de la méthode pour générer les fichiers
generate_class_files()