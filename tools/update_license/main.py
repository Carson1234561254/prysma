from pathlib import Path
from jinja2 import Environment, FileSystemLoader

template_path = Path(__file__).parent 
template_name = "license.txt.jinja"
base_path = Path(__file__).parents[2]
extensions = {'.h','.cpp', '.jinja'}


def check_license_file(path: Path):

    lignes = path.read_text(encoding="utf-8").splitlines()
    if not lignes:
        return False
    return "C++ -*-===//" in lignes[0]


def calculate_dashes(filename: str) -> int:
    total_length = 76
    fixed_length = 18  # //===-- ... ---*- C++ -*-===//
    available_for_dashes = total_length - fixed_length - len(filename) - 2 
    return max(available_for_dashes, 1)  


def update_license(path : Path, current_content):

    env = Environment(loader=FileSystemLoader(str(template_path)))
    template = env.get_template(template_name)
    file_lines = current_content.splitlines()

    num_dashes = calculate_dashes(path.name)
    context = {
        "path_file": path.name,
        "num_dashes": num_dashes
    }
    header = template.render(**context)
    new_header_lines = header.splitlines()

    if check_license_file(path) is not True:   
        if path.resolve() != (template_path / template_name).resolve():
            with open(path, 'w') as f:
                f.write(header + "\n\n" + current_content)
    else:
        if path.resolve() != (template_path / template_name).resolve():
            nb_lines_to_replace = len(new_header_lines)
            file_lines[:nb_lines_to_replace] = new_header_lines
            path.write_text("\n".join(file_lines) + "\n", encoding="utf-8")
            print(f"[UPDATED] {path.name}")

def main():

    for path in base_path.rglob('*'):
        if path.is_file() and path.suffix in extensions:
            current_content = path.read_text("utf-8")
            update_license(path, current_content)
          
if __name__ == "__main__":
    main()