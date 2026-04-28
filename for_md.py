import os
import sys



def generate_tree(dir_path, ignore_dirs, ignore_files=None, prefix=""):
    """递归生成目录树字符串"""
    if not os.path.exists(dir_path):
        return ""
    
    if ignore_files is None:
        ignore_files = set()
        
    tree_str = ""
    try:
        items = sorted(os.listdir(dir_path))
    except PermissionError:
        return prefix + "├── [Permission Denied]\n"

    # 过滤掉忽略的文件夹、忽略的文件和隐藏文件
    items = [item for item in items if item not in ignore_dirs and item not in ignore_files and not item.startswith('.')]
    
    for i, item in enumerate(items):
        item_path = os.path.join(dir_path, item)
        is_last = (i == len(items) - 1)
        
        current_prefix = "└── " if is_last else "├── "
        tree_str += prefix + current_prefix + item + ("/" if os.path.isdir(item_path) else "") + "\n"
        
        if os.path.isdir(item_path):
            next_prefix = prefix + ("    " if is_last else "│   ")
            tree_str += generate_tree(item_path, ignore_dirs, ignore_files, next_prefix)
            
    return tree_str

def merge_code_to_markdown(source_folder):
    """
    读取指定路径，合并代码，并自动在根目录下生成 AI 友好的 markdown 知识库文件
    """
    # ================= 配置区域 =================
    IGNORE_EXTS = {
        '.png', '.jpg', '.jpeg', '.gif', '.exe', '.dll', '.so', '.o',
        '.user', '.lock', '.zip', '.tar', '.gz', '.pdf',
        '.class', '.pyc', '.a', '.lib'
    }

    IGNORE_DIRS = {
        '.git', '.idea', '.vscode', '__pycache__', 'build',
        'dist', 'node_modules', 'bin', 'obj', 'cmake-build-debug',
        'cmake-build-release', 'GeneratedFiles'
    }

    EXCLUDE_FILES = set()

    BUILD_FILES_PATTERN = {
        'CMakeLists.txt', 'Makefile', 'makefile', 'GNUmakefile',
        '.pro', '.cmake', '.pri', '.prf', '.qmake.conf'
    }
    # ===========================================

    source_folder = source_folder.strip().strip("'").strip('"')
    source_folder = os.path.abspath(source_folder)

    if not os.path.exists(source_folder):
        print(f"\n❌ 错误：找不到路径 -> {source_folder}")
        return

    project_name = os.path.basename(source_folder)
    output_filename = f"{project_name}_knowledge_base.md"
    EXCLUDE_FILES.add(output_filename)
    output_file_path = os.path.join(source_folder, output_filename)

    print(f"\n📂 正在扫描项目：{project_name}")
    print(f"📝 准备生成文件：{output_filename}")
    print("-" * 30)

    # ========== 第一步：收集所有构建文件 ==========
    build_files = []
    for root, dirs, files in os.walk(source_folder):
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        for file in files:
            if file in EXCLUDE_FILES:
                continue

            # 过滤 Qt 自动生成的中间代码文件
            if file.startswith(('moc_', 'qrc_')) or (file.startswith('ui_') and file.endswith('.h')):
                continue

            file_path = os.path.join(root, file)
            if os.path.abspath(file_path) == output_file_path:
                continue

            file_name = os.path.basename(file)
            file_ext = os.path.splitext(file)[1].lower()
            is_build_file = False

            if file_name in BUILD_FILES_PATTERN or file_ext in BUILD_FILES_PATTERN:
                is_build_file = True

            if is_build_file:
                relative_path = os.path.relpath(file_path, source_folder)
                build_files.append((relative_path, file_path))

    # ========== 第二步：写入文件 ==========
    try:
        with open(output_file_path, 'w', encoding='utf-8') as outfile:
            # 1. 写入项目标题与目录树
            outfile.write(f"# 项目: {project_name}\n\n")
            
            outfile.write("## 项目目录结构\n")
            outfile.write("```text\n")
            outfile.write(f"{project_name}/\n")
            outfile.write(generate_tree(source_folder, IGNORE_DIRS, EXCLUDE_FILES))
            outfile.write("```\n\n")
            outfile.write("---\n\n")

            # 2. 写入项目特征总结
            outfile.write("## 项目特征总结\n")
            outfile.write("> [!NOTE]\n")
            outfile.write("> 此处可填写项目架构、核心技术栈及 AI 提示词（Prompt）。\n\n")
            outfile.write("\n" * 3)
            outfile.write("---\n\n")

            # 3. 写入构建文件
            if build_files:
                outfile.write("## 构建配置文件\n")
                outfile.write("---\n\n")
                for rel_path, abs_path in build_files:
                    try:
                        with open(abs_path, 'r', encoding='utf-8') as infile:
                            content = infile.read()

                        file_name = os.path.basename(abs_path)
                        file_ext = os.path.splitext(abs_path)[1].lower()
                        if file_name == 'CMakeLists.txt' or file_ext == '.cmake':
                            lang_tag = 'cmake'
                        elif file_ext in ['.pro', '.pri', '.prf']:
                            lang_tag = 'qmake'
                        elif 'makefile' in file_name.lower():
                            lang_tag = 'makefile'
                        else:
                            lang_tag = 'plaintext'

                        outfile.write(f"### File: `{rel_path}`\n")
                        outfile.write(f"<file_block path=\"{rel_path}\" type=\"build\">\n\n")
                        outfile.write(f"```{lang_tag}\n")
                        outfile.write(content)
                        outfile.write(f"\n```\n")
                        outfile.write(f"</file_block>\n\n")
                        outfile.write("---\n\n")
                        print(f"✅ 已合并构建文件: {rel_path}")

                    except UnicodeDecodeError:
                        print(f"⚠️  跳过二进制/非UTF-8构建文件: {rel_path}")
                    except Exception as e:
                        print(f"❌ 读取构建文件错误 {rel_path}: {e}")

            # 4. 写入普通源文件
            outfile.write("## 项目源文件\n")
            outfile.write("---\n\n")
            file_count = 0

            header_files = []
            source_files = []
            ui_files = []

            for root, dirs, files in os.walk(source_folder):
                dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
                for file in files:
                    if file in EXCLUDE_FILES:
                        continue

                    if file.startswith(('moc_', 'qrc_')) or (file.startswith('ui_') and file.endswith('.h')):
                        continue

                    file_path = os.path.join(root, file)
                    if os.path.abspath(file_path) == output_file_path:
                        continue

                    rel_path_check = os.path.relpath(file_path, source_folder)
                    if any(rel_path_check == bf[0] for bf in build_files):
                        continue

                    file_ext = os.path.splitext(file)[1].lower()
                    if file_ext in IGNORE_EXTS:
                        continue

                    ALLOW_EXTS = {
                        '.cpp', '.h', '.c', '.hpp', '.cppm', '.cc', '.cxx',
                        '.py', '.java', '.js', '.ts', '.html', '.css',
                        '.md', '.txt', '.json', '.toml', '.dat', '.xml', '.sql', '.sh',
                        '.ui'
                    }
                    if file_ext not in ALLOW_EXTS:
                        continue

                    relative_path = os.path.relpath(file_path, source_folder)
                    
                    if file_ext in ['.h', '.hpp', '.hxx', '.hh']:
                        header_files.append((relative_path, file_path, file_ext))
                    elif file_ext == '.ui':
                        ui_files.append((relative_path, file_path, file_ext))
                    else:
                        source_files.append((relative_path, file_path, file_ext))

            categories = [
                ("1. 头文件（Header Files）", header_files, "header"),
                ("2. 源文件（Source Files）", source_files, "source"),
                ("3. 界面设计文件（Qt UI Files）", ui_files, "ui")
            ]

            for title, files, type_tag in categories:
                if files:
                    outfile.write(f"### {title}\n")
                    outfile.write("---\n\n")
                    for rel_path, abs_path, f_ext in files:
                        try:
                            with open(abs_path, 'r', encoding='utf-8') as infile:
                                content = infile.read()

                            lang_tag = f_ext.replace('.', '')
                            if lang_tag in ['h', 'hpp', 'hxx', 'hh']:
                                lang_tag = 'cpp'
                            elif lang_tag == 'ui':
                                lang_tag = 'xml'

                            outfile.write(f"#### File: `{rel_path}`\n")
                            outfile.write(f"<file_block path=\"{rel_path}\" type=\"{type_tag}\">\n\n")
                            outfile.write(f"```{lang_tag}\n")
                            outfile.write(content)
                            outfile.write(f"\n```\n")
                            outfile.write(f"</file_block>\n\n")
                            outfile.write("---\n\n")

                            print(f"✅ 已合并源文件: {rel_path}")
                            file_count += 1

                        except UnicodeDecodeError:
                            print(f"⚠️  跳过二进制或非UTF-8源文件: {rel_path}")
                        except Exception as e:
                            print(f"❌ 读取源文件错误 {rel_path}: {e}")

            print("-" * 30)
            print(f"🎉 处理完成！")
            print(f"📦 构建文件数量: {len(build_files)}")
            print(f"📄 源文件数量: {file_count}")


    except PermissionError:
        print("❌ 错误：没有权限写入文件。")
    except Exception as e:
        print(f"❌ 发生未知错误: {e}")

if __name__ == "__main__":
    try:
        print("\n=== 代码转 Markdown 知识库工具 ===")
        if len(sys.argv) > 1:
            input_path = sys.argv[1]
        else:
            input_path = input("请输入项目根目录路径 (可直接拖入文件夹): ").strip()
            
        if input_path:
            merge_code_to_markdown(input_path)
        else:
            print("未输入路径，程序退出。")
    except KeyboardInterrupt:
        print("\n\n程序已手动取消。")
