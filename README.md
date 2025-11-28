📘 Personal Digital Diary, Notes & Story Manager

A private, modern, all-in-one writing space built for everyday thoughts, stories, and quick notes.

✨ About This Project

  This project started from a simple personal need.
  
  I enjoy writing diaries and stories, but there were two big problems:
     1> I didn’t want to carry a notebook everywhere.
     2> I was worried about privacy, because anyone could flip the notebook open.
  
  So I decided to create my own digital diary system — something that stays on my device, keeps my thoughts private, and feels as personal as a real notebook.
  That idea slowly evolved into a complete Personal Organizer, with:
  📔 Diary Mode
  📝 Notes Mode
  📚 Story Mode
  Everything is beautifully designed, private, and easy to use.

🌟 Features
  📔 Diary Mode
  
      Add diary entries with date
      Search entries by date
      Delete specific entries
      Show all saved dates
      Read entries in a handwriting-style notebook page
      Navigate using Previous / Next entry
      Dates sorted automatically (Newest → Oldest)
      Calendar popup for selecting dates
  
  📝 Notes Mode
  
      Quickly add short notes
      View all saved notes
      Delete the last note
      Clean and simple UI
  
  📚 Story Mode
  
      Create full stories
      Add multiple chapters
      Read stories one chapter at a time
      Previous/Next chapter navigation
      Edit individual chapters
      Delete entire stories
      Bookmark a specific chapter and continue later
  
  🔐 Privacy
      
      Everything is stored locally on your machine
      No cloud storage, no online syncing
      Protected login system
      Your diary stays private — just like a real one
  
  🛠️ Tech Stack
  
      This project combines both C programming (DSA) and Flask web development, making it a unique hybrid project.
      Backend Logic (C Language)
      Binary Search Tree (BST) for diary entries
      Linked List for notes
      Nested Linked Structures for stories and chapters
      File handling for long-term storage
      Clean modular structure (diary.c, notes.c, story.c)
      Web Application (Python + Flask)
      Flask routing
      Sessions & login
      File reading/writing
      HTML templates (Jinja2)
      CSS for beautiful UI
      Frontend
      Modern UI/UX
      Animated backgrounds
      Gradient color schemes
      Notebook-style diary reading page
      Handwriting font (Dancing Script)
      Fully responsive cards and layouts
    

🧠 Why This Project Is Useful

    Private and offline — data stays with you
    
    Lightweight, fast, and simple
    
    Useful for journaling, creative writing, or personal notes
    
    Helps maintain daily thoughts and habit tracking
    
    A great alternative to carrying physical notebooks
    
    Can grow into a bigger personal life-manager app

🎯 Objective of the Project

    The main goal was to create a personal, secure, and easy digital writing companion that captures:
    
    Daily diary entries
    
    Thoughts and quick reminders
    
    Stories and multi-chapter writing
    
    It also showcases how data structures (BSTs, linked lists) can be used in real-life applications.

🚀 How It Works
    1️⃣ Start the Flask Server
    python server.py
    
    2️⃣ Open browser
    http://127.0.0.1:5000/
    
    3️⃣ Login
    
    Use the default credentials (local use only):
    
    username: admin  
    password: 1234
    
    4️⃣ Choose a Mode
    
    Diary
    
    Notes
    
    Story

    Everything works through a beautiful web interface.

📄 File Structure (Important for Viewers)
📁 PBL3SEM_Final
│── server.py                # Flask app
│── diary.txt                # Diary data
│── notes.txt                # Notes data
│── stories/                 # Story files
│── bookmark.txt             # Saves last chapter
│
├── C_code/
│   ├── diary.c
│   ├── diary.h
│   ├── notes.c
│   ├── notes.h
│   ├── story.c
│   ├── story.h
│   └── main.c
│
└── templates/
    ├── diary.html
    ├── notes.html
    ├── story.html
    ├── read_diary.html
    ├── read_story.html
    ├── edit.html
    ├── login.html
    ├── index.html

🧩 What Makes This Project Special

      It comes from a real personal need
      
      It merges Data Structures + Web Development
      
      Fully functional diary + notes + story system
      
      Modern UI makes it feel like a real notebook app
      
      Offline, secure, private
      
      Most student projects are theoretical —
      this one is practical, beautiful, and personally meaningful.

💡 What I Learned
    
      Through this project, I learned:  
      How to apply DSA in real-world apps
      How to manage persistent file-based storage  
      How to build a multi-page Flask app
      How to design clean UI and organize user flows
      How to handle reading/writing structured text files
      How full-stack systems think end-to-end

📌 Future Enhancements
      Dark mode
      Cloud sync
      Mobile responsive version
      Tagging diary entries
      Export story as a PDF
      Voice-to-text diary entries

❤️ Final Thoughts

This project began as a small idea because I wanted a private, portable diary.
It grew into a fully-featured organizer with:
    
      ✔ Beautiful UI
      ✔ Secure backend
      ✔ Practical features
      ✔ Smooth DSA logic
      ✔ Real-world use

And the entire system reflects exactly why I love programming —
building something meaningful for myself.
