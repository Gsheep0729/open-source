import os
import sys

def merge_code_to_markdown(source_folder):
    """
    读取指定路径，合并代码，并自动在根目录下生成 markdown 文件
    """

    # ================= 配置区域 =================
    # 1. 想要排除的文件后缀 (增加了 .cmake)
    IGNORE_EXTS = {
        '.png', '.jpg', '.jpeg', '.gif', '.exe', '.dll', '.so', '.o',
        '.user', '.lock', '.cmake', '.zip', '.tar', '.gz', '.pdf'
    }

    # 2. 想要排除的文件夹
    IGNORE_DIRS = {
        '.git', '.idea', '.vscode', '__pycache__', 'build',
        'dist', 'node_modules', 'bin', 'obj', 'cmake-build-debug'
    }

    # 3. 想要排除的特定文件名
    EXCLUDE_FILES = {'CMakeLists.txt'}
    # ===========================================

    # 1. 路径预处理
    # 去除首尾的引号（防止拖拽路径产生引号）和空格
    source_folder = source_folder.strip().strip("'").strip('"')

    # 转换为绝对路径，防止相对路径出错
    source_folder = os.path.abspath(source_folder)

    if not os.path.exists(source_folder):
        print(f"\n❌ 错误：找不到路径 -> {source_folder}")
        return

    # 2. 自动生成输出文件名
    # 获取项目文件夹名称 (例如 /a/b/demo -> demo)
    project_name = os.path.basename(source_folder)
    output_filename = f"{project_name}_knowledge_base.md"

    # 将输出文件加入排除列表，防止自读取
    EXCLUDE_FILES.add(output_filename)

    # 组合输出文件的完整路径
    output_file_path = os.path.join(source_folder, output_filename)

    print(f"\n📂 正在扫描项目：{project_name}")
    print(f"📝 准备生成文件：{output_file_path}")
    print("-" * 30)

    try:
        with open(output_file_path, 'w', encoding='utf-8') as outfile:
            # 写入 Markdown 头部信息
            outfile.write(f"# 项目: {project_name}\n\n")
            outfile.write(f"> 生成时间: {os.popen('date').read().strip()}\n")
            outfile.write(f"> 来源路径: {source_folder}\n\n")

            file_count = 0

            for root, dirs, files in os.walk(source_folder):
                # 过滤目录
                dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]

                for file in files:
                    # 1. 文件名排除检查
                    if file in EXCLUDE_FILES:
                        continue

                    file_ext = os.path.splitext(file)[1].lower()

                    # 2. 后缀排除检查
                    if file_ext in IGNORE_EXTS:
                        continue

                    # 3. 允许的代码后缀白名单
                    ALLOW_EXTS = {
                        '.cpp', '.h', '.c', '.hpp', '.cppm', '.cc', '.cxx',
                        '.py', '.java', '.js', '.ts', '.html', '.css',
                        '.md', '.txt', '.json', '.toml', '.dat', '.xml', '.sql', '.sh'
                    }
                    if file_ext not in ALLOW_EXTS:
                        continue

                    file_path = os.path.join(root, file)

                    # 双重保险：防止读取到输出文件
                    if os.path.abspath(file_path) == output_file_path:
                        continue

                    relative_path = os.path.relpath(file_path, source_folder)

                    try:
                        with open(file_path, 'r', encoding='utf-8') as infile:
                            content = infile.read()

                        # 确定代码块语言标记
                        lang_tag = file_ext.replace('.', '')
                        if lang_tag == 'h' or lang_tag == 'hpp': lang_tag = 'cpp'

                        # 写入内容
                        outfile.write(f"## File: {relative_path}\n")
                        outfile.write(f"```{lang_tag}\n")
                        outfile.write(content)
                        outfile.write(f"\n```\n\n")
                        outfile.write("---\n\n")

                        print(f"✅ 已合并: {relative_path}")
                        file_count += 1

                    except UnicodeDecodeError:
                        print(f"⚠️  跳过二进制或非UTF-8文件: {relative_path}")
                    except Exception as e:
                        print(f"❌ 读取错误 {relative_path}: {e}")

            print("-" * 30)
            print(f"🎉 处理完成！共合并 {file_count} 个文件。")
            print(f"💾 文件位置: {output_file_path}")

    except PermissionError:
        print("❌ 错误：没有权限写入文件，请检查目录权限。")
    except Exception as e:
        print(f"❌ 发生未知错误: {e}")

if __name__ == "__main__":
    try:
        # 交互式输入路径
        print("\n=== 代码转 Markdown 知识库工具 ===")
        input_path = input("请输入项目根目录路径 (可直接拖入文件夹): ").strip()

        if input_path:
            merge_code_to_markdown(input_path)
        else:
            print("未输入路径，程序退出。")

    except KeyboardInterrupt:
        print("\n\n程序已手动取消。")
