from flask import Flask, render_template, request, redirect, session
import os

app = Flask(__name__)
app.secret_key = "supersecretkey"

DIARY_FILE = "diary.txt"
NOTES_FILE = "notes.txt"
STORY_DIR = "stories"
BOOKMARK_FILE = "bookmark.txt"

os.makedirs(STORY_DIR, exist_ok=True)

USERNAME = "admin"
PASSWORD = "1234"


@app.route("/", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        if request.form["username"] == USERNAME and request.form["password"] == PASSWORD:
            session["user"] = USERNAME
            return redirect("/home")
        return render_template("login.html", error="Invalid username or password")
    return render_template("login.html")


@app.route("/home")
def home():
    if "user" not in session:
        return redirect("/")
    return render_template("index.html")


# ============================================================
#                      DIARY MODE 
# ============================================================

def load_all_entries():
    entries = []
    if os.path.exists(DIARY_FILE):
        with open(DIARY_FILE, "r", encoding="utf-8") as f:
            for line in f:
                if "|" in line:
                    date, entry = line.split("|", 1)
                    entries.append((date.strip(), entry.strip()))

    try:
        entries.sort(
            key=lambda x: tuple(reversed(x[0].split("/"))),  
            reverse=True
        )
    except:
        pass

    return entries


@app.route("/diary")
def diary():
    return render_template("diary.html", results=None)


@app.route("/add_entry", methods=["POST"])
def add_entry():
    date = request.form["date"].strip()
    entry = request.form["entry"].strip()

    with open(DIARY_FILE, "a", encoding="utf-8") as f:
        f.write(f"{date} | {entry}\n")

    return redirect("/diary")


@app.route("/show_all", methods=["POST"])
def show_all():
    entries = load_all_entries()
    dates = [d for d, e in entries]
    return render_template("diary.html", results=dates)


@app.route("/search_entry", methods=["POST"])
def search_entry():
    date = request.form["search_date"].strip()

    entries = load_all_entries()
    found = [d for d, e in entries if d == date]

    return render_template("diary.html", results=found)


@app.route("/delete_entry", methods=["POST"])
def delete_entry():
    date = request.form["delete_date"].strip()

    if not os.path.exists(DIARY_FILE):
        return render_template("diary.html", delete_message="Diary file not found.")

    with open(DIARY_FILE, "r", encoding="utf-8") as f:
        lines = f.readlines()

    new_lines = [line for line in lines if not line.startswith(date)]
    deleted = len(lines) != len(new_lines)

    with open(DIARY_FILE, "w", encoding="utf-8") as f:
        f.writelines(new_lines)

    msg = "Entry deleted successfully." if deleted else "No entry found."
    return render_template("diary.html", delete_message=msg)

@app.route("/read_entry/<path:date>")
def read_entry(date):
    
    safe_date = date.replace("-", "/")

    entries = load_all_entries() 
    text = ""
    index = None

    for i, (d, e) in enumerate(entries):
        if d == safe_date:
            text = e
            index = i
            break

    prev_url = None
    next_url = None

    if index is not None:
        
        if index + 1 < len(entries):
            prev_date = entries[index + 1][0]          
            prev_url = prev_date.replace("/", "-")     

        if index - 1 >= 0:
            next_date = entries[index - 1][0]
            next_url = next_date.replace("/", "-")

    return render_template(
        "read_diary.html",
        date=safe_date,
        entry=text,
        prev_date=prev_url,
        next_date=next_url
    )


# ============================================================
#                      NOTES MODE
# ============================================================

@app.route("/notes")
def notes():
    notes_list = []
    if os.path.exists(NOTES_FILE):
        with open(NOTES_FILE, "r", encoding="utf-8") as f:
            notes_list = [line.strip() for line in f.readlines()]
    return render_template("notes.html", notes=notes_list)


@app.route("/add_note", methods=["POST"])
def add_note():
    note = request.form["note"].strip()
    with open(NOTES_FILE, "a", encoding="utf-8") as f:
        f.write(note + "\n")
    return redirect("/notes")


@app.route("/delete_last_note", methods=["POST"])
def delete_last_note():
    if os.path.exists(NOTES_FILE):
        with open(NOTES_FILE, "r", encoding="utf-8") as f:
            lines = f.readlines()
        if lines:
            lines.pop()
            with open(NOTES_FILE, "w", encoding="utf-8") as f:
                f.writelines(lines)
    return redirect("/notes")


# ============================================================
#                      STORY MODE
# ============================================================

def parse_story(path):
    chapters = []
    if not os.path.exists(path):
        return chapters

    with open(path, "r", encoding="utf-8") as f:
        raw = f.read().strip()

    blocks = raw.split("### ")
    for b in blocks:
        if not b.strip():
            continue
        parts = b.split("\n", 1)
        title = parts[0].strip()
        content = parts[1].strip() if len(parts) > 1 else ""
        chapters.append({"title": title, "content": content})

    return chapters


def save_story(path, chapters):
    with open(path, "w", encoding="utf-8") as f:
        for c in chapters:
            f.write(f"### {c['title']}\n{c['content']}\n\n")


@app.route("/story")
def story():
    stories = [f[:-4] for f in os.listdir(STORY_DIR) if f.endswith(".txt")]

    bookmark_story = None
    bookmark_chapter = None

    if os.path.exists(BOOKMARK_FILE):
        with open(BOOKMARK_FILE, "r") as f:
            data = f.read().strip().split("|")
            if len(data) == 2:
                bookmark_story = data[0]
                bookmark_chapter = int(data[1])

    return render_template("story.html",
                           stories=stories,
                           bookmark_story=bookmark_story,
                           bookmark_chapter=bookmark_chapter)


@app.route("/create_story", methods=["POST"])
def create_story():
    name = request.form["story_name"].strip()
    if name:
        open(os.path.join(STORY_DIR, f"{name}.txt"), "a").close()
    return redirect("/story")


@app.route("/add_chapter", methods=["POST"])
def add_chapter():
    story_name = request.form["story_name"]
    title = request.form["chapter_title"]
    content = request.form["chapter_content"]

    with open(os.path.join(STORY_DIR, f"{story_name}.txt"), "a", encoding="utf-8") as f:
        f.write(f"### {title}\n{content}\n\n")
    return redirect("/story")


@app.route("/read_story", methods=["POST"])
def read_story_redirect():
    story_name = request.form["story_name"]
    return redirect(f"/read_story/{story_name}/0")


@app.route("/read_story/<story>/<int:index>")
def read_story(story, index):
    chapters = parse_story(os.path.join(STORY_DIR, story + ".txt"))

    if not chapters:
        return render_template("story.html", stories=[], story_name=story)

    index = max(0, min(index, len(chapters) - 1))

    return render_template("read_story.html",
                           story_name=story,
                           chapter=chapters[index],
                           index=index,
                           total=len(chapters))


@app.route("/edit_story_redirect/<story_name>")
def edit_story_redirect(story_name):
    return redirect(f"/edit_story/{story_name}/0")


@app.route("/edit_story/<story_name>/<int:index>", methods=["GET", "POST"])
def edit_story(story_name, index):
    path = os.path.join(STORY_DIR, story_name + ".txt")
    chapters = parse_story(path)
    index = max(0, min(index, len(chapters) - 1))

    if request.method == "POST":
        chapters[index]["content"] = request.form.get("content", "")
        save_story(path, chapters)
        return redirect(f"/read_story/{story_name}/{index}")

    return render_template("edit.html",
                           mode="Story",
                           entry=chapters[index]["content"],
                           story_name=story_name,
                           chapter_index=index)


@app.route("/bookmark", methods=["POST"])
def bookmark():
    with open(BOOKMARK_FILE, "w") as f:
        f.write(f"{request.form['story_name']}|{request.form['chapter_index']}")
    return redirect("/story")


@app.route("/story/delete/<story>", methods=["POST"])
def delete_story(story):
    path = os.path.join(STORY_DIR, story + ".txt")
    if os.path.exists(path):
        os.remove(path)
    return redirect("/story")


# ============================================================
#                     RUN SERVER
# ============================================================

if __name__ == "__main__":
    app.run(debug=True)
