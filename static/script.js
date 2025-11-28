
// ---------- DIARY MODE ----------
async function addDiary() {
  const date = document.getElementById("diaryDate").value;
  const text = document.getElementById("diaryText").value;
  const res = await fetch("/diary/add", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ date, text }),
  });
  alert((await res.json()).message);
}

async function viewDiary() {
  const res = await fetch("/diary/view");
  const data = await res.json();
  const div = document.getElementById("diaryDisplay");
  div.innerHTML = data.map(e => `<p><b>${e.date}</b>: ${e.text}</p>`).join("");
}

async function searchDiary() {
  const date = prompt("Enter date (DD/MM/YYYY):");
  const res = await fetch(`/diary/search/${date}`);
  const data = await res.json();
  alert(data.found ? `Entry: ${data.entry}` : "No entry found.");
}

async function deleteDiary() {
  const date = prompt("Enter date to delete:");
  const res = await fetch(`/diary/delete/${date}`, { method: "DELETE" });
  alert((await res.json()).message);
}

// ---------- NOTES MODE ----------
async function addNote() {
  const text = document.getElementById("noteText").value;
  const res = await fetch("/notes/add", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ text }),
  });
  alert((await res.json()).message);
}

async function viewNotes() {
  const res = await fetch("/notes/view");
  const data = await res.json();
  const div = document.getElementById("noteDisplay");
  div.innerHTML = data.map(n => `<p>- ${n}</p>`).join("");
}

async function deleteLastNote() {
  const res = await fetch("/notes/delete_last", { method: "DELETE" });
  alert((await res.json()).message);
}

// ---------- STORY MODE ----------
async function createStory() {
  const title = document.getElementById("storyTitle").value;
  const res = await fetch("/story/create", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ title }),
  });
  alert((await res.json()).message);
}

async function addChapter() {
  const title = document.getElementById("storyTitle").value;
  const chapter = document.getElementById("chapterText").value;
  const res = await fetch("/story/add_chapter", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ title, chapter }),
  });
  alert((await res.json()).message);
}

async function readStory() {
  const title = document.getElementById("storyTitle").value;
  const res = await fetch(`/story/read/${encodeURIComponent(title)}`);
  const data = await res.json();
  const div = document.getElementById("storyDisplay");
  div.innerHTML = data.chapters
    .map((ch, i) => `<h3>Chapter ${i + 1}</h3><p>${ch}</p>`)
    .join("<hr>");
}

async function saveBookmark() {
  const title = document.getElementById("bookmarkStory").value;
  const chapter = document.getElementById("bookmarkChapter").value;
  const res = await fetch("/story/bookmark", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ title, chapter }),
  });
  alert((await res.json()).message);
}

async function viewBookmark() {
  const res = await fetch("/story/bookmark");
  const data = await res.json();
  document.getElementById("bookmarkDisplay").innerText =
    data.title === "None"
      ? "No bookmarks saved."
      : `Story: ${data.title}, Chapter: ${data.chapter}`;
}

async function continueFromBookmark() {
  const res = await fetch("/story/bookmark");
  const data = await res.json();
  if (data.title === "None") return alert("No bookmark found!");
  const res2 = await fetch(`/story/read/${encodeURIComponent(data.title)}`);
  const story = await res2.json();
  const chapterIndex = parseInt(data.chapter) - 1;
  if (chapterIndex < 0 || chapterIndex >= story.chapters.length)
    return alert("Invalid bookmark chapter!");
  const div = document.getElementById("storyDisplay");
  div.innerHTML = `<h3>${data.title} - Chapter ${data.chapter}</h3><p>${story.chapters[chapterIndex]}</p>`;
}
