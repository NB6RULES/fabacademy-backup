+++
title = "Week 15 - Interface and Application Programming"
weight = 115
bookCollapseSection = true
+++

# Week 15 - Interface and Application Programming

Week 15 focused on **interface and application programming**, learning to create user interfaces that communicate with embedded systems.  
The aim was to develop applications that provide meaningful interaction between users and fabricated devices.

This week brought together the hardware skills with software development for complete interactive systems.

---

## Group Assignment
- Compare as many **tool options** as possible for interface development

## Individual Assignment
- Write an **application** that interfaces a user with an input &/or output device that you made

**Extra Credit Goals**
- Try **multiple programming languages** or frameworks
- Implement **real-time data visualization**
- Create a **mobile or web application**

---

## What I Learned

This week was lowkey a different vibe compared to the rest of Fab Academy — most weeks are about *making the hardware*, this one was about putting a usable interface on top of hardware. Also the first week where I leaned heavily on AI design tools end-to-end, which was a workflow I hadn't really tried before.

- How to actually plan a UI before opening any design tool — the Claude web interface walked me through the right questions (audience, core jobs, screens, fidelity) and that planning step did most of the work
- **Google Stitch** for going from a rough idea to a mockup in minutes — uploading the first prototype and getting back a designed-out version felt basically like sketching with a much faster pencil
- **Claude Design** for taking the Stitch mockup further into an actual clickable Flutter prototype — the "handoff to Claude Code" flow was new to me and genuinely useful
- How to use **Codemagic** to take a Flutter repo on GitHub and build a real `.ipa` for iOS — no Mac, no Xcode, no Apple Developer account dance, just point it at the repo and let it build
- Most importantly — the AI-design tool chain isn't a replacement for design thinking, it's a speed multiplier on top of it. The hours I would've spent fighting Figma went into actually deciding what the app *should do* 🤌

---

## Weekly Schedule

| Day | What I Did |
|-----|-----------|
| WED | Lecture on interface and application programming |
| THU | Local Lecture at Superfablab Kochi |
| FRI | UI planning with the Claude web interface — web app prototype |
| SAT | Google Stitch — mobile mockup from the web prototype |
| SUN | Claude Design — Flutter prototype + handoff to Claude Code |
| MON | Push to GitHub + Codemagic build → working iOS app |
| TUE | Regional review |

---

# Planning

For this project, I am planning to build a smart toolbox that can track whether tools are present or missing. Each tool will be placed on a switch, so when a tool is removed, the system can detect it. I will also use RFID to identify who is opening the toolbox and taking tools. Along with the hardware, I plan to develop a simple web app that shows all tools in real time, highlighting missing ones. There will also be an admin view to see who took which tool and when. This project is being developed at Super Fablab Kerala to make tool management easier and more organized.


<!--
  ╔══════════════════════════════════════════════════════════════╗
  ║  SUPER FABLAB KERALA — TOOL CABINET WIDGET (FULL)           ║
  ║  Hugo embed snippet — Tool Status + Admin Panel             ║
  ║                                                              ║
  ║  SETUP:                                                      ║
  ║  1. Replace SUPABASE_URL and SUPABASE_ANON_KEY below        ║
  ║  2. In Hugo, paste inside a raw HTML block:                 ║
  ║     {{< rawhtml >}} ... {{< /rawhtml >}}                    ║
  ╚══════════════════════════════════════════════════════════════╝
-->
{{< rawhtml >}} 
<style>
  @import url('https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=DM+Sans:wght@400;500;600&display=swap');

  .sfl-widget * { box-sizing: border-box; margin: 0; padding: 0; }

  .sfl-widget {
    --bg:      #0e0f11;
    --bg2:     #161719;
    --bg3:     #1e1f22;
    --border:  #2a2b2f;
    --green:   #22c55e;
    --red:     #f43f5e;
    --amber:   #f59e0b;
    --text:    #e4e4e7;
    --muted:   #71717a;
    --accent:  #a78bfa;
    font-family: 'DM Sans', sans-serif;
    background: var(--bg);
    border: 1px solid var(--border);
    border-radius: 14px;
    overflow: hidden;
    max-width: 540px;
    color: var(--text);
    font-size: 13px;
    box-shadow: 0 8px 40px rgba(0,0,0,0.55);
  }

  /* ── Header ── */
  .sfl-header {
    padding: 14px 18px 10px;
    border-bottom: 1px solid var(--border);
    display: flex;
    align-items: center;
    justify-content: space-between;
    background: var(--bg2);
  }
  .sfl-brand-name {
    font-family: 'Space Mono', monospace;
    font-size: 11px;
    font-weight: 700;
    color: var(--accent);
    letter-spacing: .06em;
    text-transform: uppercase;
  }
  .sfl-brand-sub { font-size: 10px; color: var(--muted); margin-top: 1px; }
  .sfl-live {
    display: flex; align-items: center; gap: 5px;
    font-family: 'Space Mono', monospace;
    font-size: 9px; font-weight: 700;
    letter-spacing: .1em; color: var(--green); text-transform: uppercase;
  }
  .sfl-live-dot {
    width: 6px; height: 6px; border-radius: 50%; background: var(--green);
    animation: sfl-pulse 2s ease-in-out infinite;
  }
  @keyframes sfl-pulse {
    0%,100% { opacity:1; transform:scale(1); }
    50%      { opacity:.4; transform:scale(.8); }
  }

  /* ── Tabs ── */
  .sfl-tabs {
    display: flex;
    padding: 10px 14px 0;
    gap: 6px;
    background: var(--bg2);
    border-bottom: 1px solid var(--border);
  }
  .sfl-tab {
    padding: 6px 14px;
    border-radius: 7px 7px 0 0;
    font-size: 11px; font-weight: 600;
    cursor: pointer;
    border: 1px solid transparent;
    border-bottom: none;
    color: var(--muted);
    background: transparent;
    transition: color .15s, background .15s;
  }
  .sfl-tab.active {
    background: var(--bg);
    border-color: var(--border);
    color: var(--text);
    margin-bottom: -1px;
  }
  .sfl-tab:not(.active):hover { color: var(--text); }

  /* ── Panel ── */
  .sfl-panel { display: none; }
  .sfl-panel.active { display: block; }

  /* ── Stats ── */
  .sfl-stats {
    display: grid; grid-template-columns: repeat(3,1fr);
    border-bottom: 1px solid var(--border);
  }
  .sfl-stat {
    padding: 12px 0; text-align: center;
    border-right: 1px solid var(--border);
  }
  .sfl-stat:last-child { border-right: none; }
  .sfl-stat-num {
    font-family: 'Space Mono', monospace;
    font-size: 22px; font-weight: 700; line-height: 1; margin-bottom: 3px;
  }
  .sfl-stat-label { font-size: 9px; text-transform: uppercase; letter-spacing: .08em; color: var(--muted); }
  .sfl-stat.total   .sfl-stat-num { color: var(--text); }
  .sfl-stat.present .sfl-stat-num { color: var(--green); }
  .sfl-stat.missing .sfl-stat-num { color: var(--red); }

  /* ── Alert ── */
  .sfl-alert {
    margin: 10px 14px;
    padding: 8px 12px;
    background: rgba(244,63,94,.08);
    border: 1px solid rgba(244,63,94,.25);
    border-radius: 8px;
    font-size: 11px; color: var(--red);
    display: flex; align-items: center; gap: 7px;
  }
  .sfl-alert.hidden { display: none; }

  /* ── Tool grid ── */
  .sfl-grid {
    display: grid; grid-template-columns: repeat(4,1fr);
    gap: 6px; padding: 10px 14px 14px;
  }
  .sfl-slot {
    background: var(--bg3); border: 1px solid var(--border);
    border-radius: 8px; padding: 8px 6px;
    display: flex; flex-direction: column; gap: 4px;
    transition: border-color .2s;
  }
  .sfl-slot.present { border-left: 2px solid var(--green); }
  .sfl-slot.missing { border-left: 2px solid var(--red); background: rgba(244,63,94,.04); }
  .sfl-slot-id { font-family: 'Space Mono', monospace; font-size: 8px; color: var(--muted); }
  .sfl-slot-name { font-size: 10px; font-weight: 600; line-height: 1.3; word-break: break-word; }
  .sfl-slot-status { display: flex; align-items: center; gap: 3px; margin-top: 2px; }
  .sfl-dot { width: 5px; height: 5px; border-radius: 50%; }
  .sfl-dot.green { background: var(--green); }
  .sfl-dot.red   { background: var(--red); animation: sfl-pulse 2s ease-in-out infinite; }
  .sfl-slot-who { font-size: 9px; color: var(--red); font-weight: 500; white-space: nowrap; overflow: hidden; text-overflow: ellipsis; }

  /* ── Admin: Filters ── */
  .sfl-filters {
    padding: 12px 14px;
    display: flex; flex-direction: column; gap: 7px;
    border-bottom: 1px solid var(--border);
  }
  .sfl-select {
    width: 100%;
    background: var(--bg3);
    border: 1px solid var(--border);
    border-radius: 8px;
    color: var(--text);
    font-family: 'DM Sans', sans-serif;
    font-size: 12px;
    padding: 8px 12px;
    appearance: none;
    cursor: pointer;
    outline: none;
    background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='12' height='12' viewBox='0 0 24 24' fill='none' stroke='%2371717a' stroke-width='2'%3E%3Cpath d='m6 9 6 6 6-6'/%3E%3C/svg%3E");
    background-repeat: no-repeat;
    background-position: right 10px center;
    padding-right: 30px;
  }
  .sfl-select:focus { border-color: var(--accent); }

  /* ── Admin: Log ── */
  .sfl-log { padding: 0 14px 14px; display: flex; flex-direction: column; gap: 6px; max-height: 340px; overflow-y: auto; }
  .sfl-log::-webkit-scrollbar { width: 4px; }
  .sfl-log::-webkit-scrollbar-track { background: transparent; }
  .sfl-log::-webkit-scrollbar-thumb { background: var(--border); border-radius: 2px; }

  .sfl-log-row {
    display: flex; align-items: center; gap: 10px;
    padding: 9px 10px;
    background: var(--bg3); border: 1px solid var(--border);
    border-radius: 9px;
    transition: border-color .15s;
  }
  .sfl-log-row:hover { border-color: #3f3f46; }

  .sfl-avatar {
    width: 30px; height: 30px; border-radius: 50%;
    display: flex; align-items: center; justify-content: center;
    font-size: 11px; font-weight: 700; flex-shrink: 0;
    font-family: 'Space Mono', monospace;
  }

  .sfl-log-info { flex: 1; min-width: 0; }
  .sfl-log-name { font-size: 12px; font-weight: 600; }
  .sfl-log-tool { font-size: 10px; color: var(--muted); white-space: nowrap; overflow: hidden; text-overflow: ellipsis; }

  .sfl-badge {
    font-size: 9px; font-weight: 700; letter-spacing: .05em;
    padding: 3px 7px; border-radius: 5px;
    text-transform: uppercase; white-space: nowrap;
  }
  .sfl-badge.out      { background: rgba(244,63,94,.15); color: var(--red); border: 1px solid rgba(244,63,94,.25); }
  .sfl-badge.returned { background: rgba(34,197,94,.12); color: var(--green); border: 1px solid rgba(34,197,94,.2); }

  .sfl-log-meta { text-align: right; flex-shrink: 0; }
  .sfl-log-slot { font-family: 'Space Mono', monospace; font-size: 9px; color: var(--muted); }
  .sfl-log-time { font-family: 'Space Mono', monospace; font-size: 9px; color: var(--muted); margin-top: 2px; }

  .sfl-empty {
    text-align: center; padding: 28px 0;
    font-size: 11px; color: var(--muted);
  }

  /* ── Footer ── */
  .sfl-footer {
    padding: 8px 14px; border-top: 1px solid var(--border);
    background: var(--bg2); display: flex; align-items: center; justify-content: space-between;
  }
  .sfl-footer-link {
    font-size: 9px; color: var(--muted); text-decoration: none;
    font-family: 'Space Mono', monospace; letter-spacing: .04em;
    transition: color .2s;
  }
  .sfl-footer-link:hover { color: var(--accent); }
  .sfl-updated { font-size: 9px; color: var(--muted); font-family: 'Space Mono', monospace; }
</style>

<div class="sfl-widget">

  <!-- Header -->
  <div class="sfl-header">
    <div>
      <div class="sfl-brand-name">Tool Cabinet</div>
      <div class="sfl-brand-sub">Super Fablab Kerala · Kochi, India</div>
    </div>
    <div class="sfl-live"><span class="sfl-live-dot"></span>Live</div>
  </div>

  <!-- Tabs -->
  <div class="sfl-tabs">
    <button class="sfl-tab active" onclick="sflTab('status', this)">Tool status</button>
    <button class="sfl-tab"        onclick="sflTab('admin',  this)">Admin panel</button>
  </div>

  <!-- ══ TOOL STATUS PANEL ══ -->
  <div class="sfl-panel active" id="sfl-panel-status">
    <div class="sfl-stats">
      <div class="sfl-stat total">
        <div class="sfl-stat-num" id="sfl-total">—</div>
        <div class="sfl-stat-label">Total tools</div>
      </div>
      <div class="sfl-stat present">
        <div class="sfl-stat-num" id="sfl-present">—</div>
        <div class="sfl-stat-label">Present</div>
      </div>
      <div class="sfl-stat missing">
        <div class="sfl-stat-num" id="sfl-missing">—</div>
        <div class="sfl-stat-label">Missing</div>
      </div>
    </div>

    <div class="sfl-alert hidden" id="sfl-alert">
      <svg width="12" height="12" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5">
        <circle cx="12" cy="12" r="10"/><line x1="12" y1="8" x2="12" y2="12"/><line x1="12" y1="16" x2="12.01" y2="16"/>
      </svg>
      <span id="sfl-alert-text"></span>
    </div>

    <div class="sfl-grid" id="sfl-grid"></div>
  </div>

  <!-- ══ ADMIN PANEL ══ -->
  <div class="sfl-panel" id="sfl-panel-admin">
    <div class="sfl-filters">
      <select class="sfl-select" id="sfl-filter-member" onchange="sflRenderLog()">
        <option value="">All members</option>
        <option>Abhishek Shah</option>
        <option>Ali Abdul Gafoor</option>
        <option>Archita B K</option>
        <option>Ardradevi K</option>
        <option>Ashtami P S</option>
        <option>Kevin Jijo</option>
        <option>Kurian Jacob</option>
        <option>Merin Cyriac</option>
        <option>Mishael Sharaf</option>
        <option>Nadec Biju</option>
      </select>
      <select class="sfl-select" id="sfl-filter-action" onchange="sflRenderLog()">
        <option value="">All actions</option>
        <option value="out">Checked out</option>
        <option value="returned">Returned</option>
      </select>
    </div>
    <div class="sfl-log" id="sfl-log"></div>
  </div>

  <!-- Footer -->
  <div class="sfl-footer">
    <a class="sfl-footer-link" href="https://fabacademy.org/2026/labs/kochi/" target="_blank" rel="noopener">
      fabacademy.org/2026/labs/kochi ↗
    </a>
    <span class="sfl-updated" id="sfl-updated"></span>
  </div>

</div> <!-- End .sfl-widget -->

<script>
(function () {
  // ── CONFIG ─────────────────────────────────────
  const SUPABASE_URL      = 'https://YOUR_PROJECT.supabase.co';
  const SUPABASE_ANON_KEY = 'YOUR_ANON_KEY';

  // ── AVATAR COLOURS per member ──────────────────
  const COLORS = {
    'Abhishek Shah':    ['#f97316','#431407'],
    'Ali Abdul Gafoor': ['#a78bfa','#2e1065'],
    'Archita B K':      ['#f43f5e','#4c0519'],
    'Ardradevi K':      ['#06b6d4','#083344'],
    'Ashtami P S':      ['#84cc16','#1a2e05'],
    'Kevin Jijo':       ['#22c55e','#052e16'],
    'Kurian Jacob':     ['#f59e0b','#451a03'],
    'Merin Cyriac':     ['#ec4899','#500724'],
    'Mishael Sharaf':   ['#38bdf8','#082f49'],
    'Nadec Biju':       ['#e879f9','#3b0764'],
  };

  function initials(name) {
    return name.split(' ').slice(0,2).map(w=>w[0]).join('').toUpperCase();
  }
  function avatar(name) {
    const c = COLORS[name] || ['#71717a','#18181b'];
    return `<div class="sfl-avatar" style="background:${c[1]};color:${c[0]}">${initials(name)}</div>`;
  }

  // ── DEMO DATA ──────────────────────────────────
  const DEMO_TOOLS = [
    { slot_id:'S-01', name:'Digital calipers',   present:true,  user:null },
    { slot_id:'S-02', name:'Soldering iron',      present:false, user:'Kevin Jijo' },
    { slot_id:'S-03', name:'Wire stripper',       present:true,  user:null },
    { slot_id:'S-04', name:'Multimeter',          present:false, user:'Nadec Biju' },
    { slot_id:'S-05', name:'Hex key set',         present:true,  user:null },
    { slot_id:'S-06', name:'Oscilloscope probe',  present:true,  user:null },
    { slot_id:'S-07', name:'Flush cutters',       present:true,  user:null },
    { slot_id:'S-08', name:'Heat gun',            present:false, user:'Archita B K' },
    { slot_id:'S-09', name:'Label maker',         present:true,  user:null },
    { slot_id:'S-10', name:'Breadboard kit',      present:true,  user:null },
    { slot_id:'S-11', name:'Crimping tool',       present:false, user:'Mishael Sharaf' },
    { slot_id:'S-12', name:'Torque screwdriver',  present:true,  user:null },
    { slot_id:'S-13', name:'PCB holder',          present:true,  user:null },
    { slot_id:'S-14', name:'USB power meter',     present:false, user:'Ali Abdul Gafoor' },
    { slot_id:'S-15', name:'Tweezers set',        present:true,  user:null },
    { slot_id:'S-16', name:'Step drill bits',     present:true,  user:null },
  ];

  const DEMO_LOG = [
    { user:'Ali Abdul Gafoor', tool:'USB power meter',    action:'out',      slot:'S-14', time:'10:42 AM' },
    { user:'Mishael Sharaf',   tool:'Crimping tool',       action:'out',      slot:'S-11', time:'10:31 AM' },
    { user:'Nadec Biju',       tool:'Multimeter',          action:'out',      slot:'S-04', time:'10:17 AM' },
    { user:'Archita B K',      tool:'Heat gun',            action:'out',      slot:'S-08', time:'9:58 AM'  },
    { user:'Kevin Jijo',       tool:'Soldering iron',      action:'out',      slot:'S-02', time:'9:45 AM'  },
    { user:'Ashtami P S',      tool:'Oscilloscope probe',  action:'returned', slot:'S-06', time:'9:30 AM'  },
    { user:'Ardradevi K',      tool:'Digital calipers',    action:'returned', slot:'S-01', time:'9:12 AM'  },
    { user:'Kurian Jacob',     tool:'Hex key set',         action:'returned', slot:'S-05', time:'9:05 AM'  },
    { user:'Abhishek Shah',    tool:'PCB holder',          action:'returned', slot:'S-13', time:'8:55 AM'  },
    { user:'Merin Cyriac',     tool:'Step drill bits',     action:'returned', slot:'S-16', time:'8:47 AM'  },
  ];

  // ── expose log globally for filter callbacks ───
  window._sflLog = DEMO_LOG;

  // ── RENDER STATUS ──────────────────────────────
  function renderStatus(tools) {
    const total   = tools.length;
    const present = tools.filter(t => t.present).length;
    const missing = total - present;

    document.getElementById('sfl-total').textContent   = total;
    document.getElementById('sfl-present').textContent = present;
    document.getElementById('sfl-missing').textContent = missing;

    const alertEl = document.getElementById('sfl-alert');
    if (missing > 0) {
      alertEl.classList.remove('hidden');
      document.getElementById('sfl-alert-text').textContent =
        `${missing} tool${missing > 1 ? 's are' : ' is'} currently checked out`;
    } else {
      alertEl.classList.add('hidden');
    }

    document.getElementById('sfl-grid').innerHTML = tools.map(t => `
      <div class="sfl-slot ${t.present ? 'present' : 'missing'}">
        <span class="sfl-slot-id">${t.slot_id}</span>
        <span class="sfl-slot-name">${t.name}</span>
        <div class="sfl-slot-status">
          <span class="sfl-dot ${t.present ? 'green' : 'red'}"></span>
          ${t.present
            ? '<span style="font-size:9px;color:var(--green)">Present</span>'
            : `<span class="sfl-slot-who">${t.user || 'Unknown'}</span>`}
        </div>
      </div>`).join('');

    document.getElementById('sfl-updated').textContent =
      new Date().toLocaleTimeString([], {hour:'2-digit', minute:'2-digit'});
  }

  // ── RENDER LOG (called on filter change too) ───
  window.sflRenderLog = function() {
    const memberFilter = document.getElementById('sfl-filter-member').value;
    const actionFilter = document.getElementById('sfl-filter-action').value;

    let rows = window._sflLog;
    if (memberFilter) rows = rows.filter(r => r.user === memberFilter);
    if (actionFilter) rows = rows.filter(r => r.action === actionFilter);

    const logEl = document.getElementById('sfl-log');
    if (rows.length === 0) {
      logEl.innerHTML = '<div class="sfl-empty">No activity found</div>';
      return;
    }

    logEl.innerHTML = rows.map(r => `
      <div class="sfl-log-row">
        ${avatar(r.user)}
        <div class="sfl-log-info">
          <div class="sfl-log-name">${r.user}</div>
          <div class="sfl-log-tool">${r.tool}</div>
        </div>
        <span class="sfl-badge ${r.action === 'out' ? 'out' : 'returned'}">
          ${r.action === 'out' ? 'Checked out' : 'Returned'}
        </span>
        <div class="sfl-log-meta">
          <div class="sfl-log-slot">${r.slot}</div>
          <div class="sfl-log-time">${r.time}</div>
        </div>
      </div>`).join('');
  };

  // ── TAB SWITCHER ───────────────────────────────
  window.sflTab = function(name, btn) {
    document.querySelectorAll('.sfl-tab').forEach(t => t.classList.remove('active'));
    document.querySelectorAll('.sfl-panel').forEach(p => p.classList.remove('active'));
    btn.classList.add('active');
    document.getElementById('sfl-panel-' + name).classList.add('active');
  };

  // ── INIT ───────────────────────────────────────
  renderStatus(DEMO_TOOLS);
  sflRenderLog();

  // ── Supabase fetch (swap in when ready) ────────
  if (!SUPABASE_URL.includes('YOUR_PROJECT')) {
    const headers = {
      'apikey': SUPABASE_ANON_KEY,
      'Authorization': `Bearer ${SUPABASE_ANON_KEY}`,
    };
    async function fetchAll() {
      const [tRes, lRes] = await Promise.all([
        fetch(`${SUPABASE_URL}/rest/v1/tools?select=slot_id,name,present,checked_out_by`, { headers }),
        fetch(`${SUPABASE_URL}/rest/v1/activity_log?select=user_name,tool_name,action,slot_id,created_at&order=created_at.desc&limit=50`, { headers }),
      ]);
      const tools = await tRes.json();
      const log   = await lRes.json();
      renderStatus(tools.map(t => ({ ...t, user: t.checked_out_by })));
      window._sflLog = log.map(r => ({
        user: r.user_name, tool: r.tool_name, action: r.action,
        slot: r.slot_id,
        time: new Date(r.created_at).toLocaleTimeString([], {hour:'2-digit', minute:'2-digit'}),
      }));
      sflRenderLog();
    }
    fetchAll();
    setInterval(fetchAll, 15000);
  }
})();
</script>
{{< /rawhtml >}} 


> **AI PROMPT USED WITH THE CLAUDE WEB INTERFACE**
>
> Let's plan a UI application. I'm building a smart toolbox that tracks the tools.
> I want a webapp that displays all the tools that are currently present in the toolbox and what all are the tools that are missing.
> There should also be an admin panel to view who all took what all tools.
>
> Q: How does the tool tracking work on the hardware side?
> A: Switches on top of which the tools would be placed.
>
> Q: Who uses the main display?
> A: Anyone with an RFID tag can open the toolbox and take the items.
>
> Q: What stack are you thinking?
> A: Doesn't matter, you pick.
>
> Names: Super Fablab Kerala (Kochi, India)
>
> Abhishek Shah ,
> Ali Abdul Gafoor ,
> Archita B K ,
> Ardradevi K ,
> Ashtami P S ,
> Kevin Jijo ,
> Kurian Jacob ,
> Merin Cyriac ,
> Mishael Sharaf ,
> Nadec Biju 


This was the initial mockup I've used to get an idea of what I'm doing and how I want to get things done. After this I had gotten somewhat ready and I wanted to move to the next level and create a mobile application, for which I have switched to the Google Stitch AI platform. I have moved to Google Stitch and uploaded the screenshot of this UI and asked it to create a mockup design of how the UI can be, and this is what it came up with.


![google stitch mockup](../../../images/week-15/stitch.jpg)

[🔗 Open the live Stitch preview](https://stitch.withgoogle.com/preview/5073354264278421526?node-id=375809142c504fa6b4a50e605eb24d67)

[Project link](https://stitch.withgoogle.com/projects/5073354264278421526) if you want to explore more and see the design in detail.


I wasn't much keen on this design by Google Stitch and I had wanted to do it in a different way and thought I would try out Claude Design. I have gone onto Claude Design and uploaded the designs by Google Stitch and asked it to create a design for the same, and this is what it came up with.
![claude design](../../../images/week-15/claude-design.jpg)


### Claude-generated prototype

{{< rawhtml >}}
<iframe
  src="../../../files/smart-tool-box-standalone.html"
  width="100%"
  height="820"
  style="border: 1px solid #2a2b2f; border-radius: 12px; display: block; margin: 20px 0;"
  loading="lazy"
  allowfullscreen>
</iframe>
<p style="font-size: 13px; color: #666; margin-top: 6px;">
  <a href="../../../files/smart-tool-box-standalone.html" target="_blank" rel="noopener">↗ Open the prototype in a new tab</a>
</p>
{{< /rawhtml >}}

> **AI PROMPT USED WITH THE CLAUDE DESIGN INTERFACE**
>
> I wanna build a flutter app for my smart tool box ,  (Inserted Screenshot of the UI design I have created in google stitch)
>
> **Questions answered:**
>
> - **Audience:** Hobbyists / makers
> - **Core jobs:** See what's in the box (inventory), Check tools out / in, Track who has what, Get alerts when tools missing
> - **Fidelity:** High-fidelity clickable prototype (recommended)
> - **Screens:** Cabinet inventory grid, Admin, Tool detail, Activity feed
> - **Variations:** Just one solid direction
> - **Aesthetic:** Light + orange (workshop)
> - **Tweaks:** Inventory layout (grid vs list), Card style, Density (compact vs roomy)
> - **Device:** Both side-by-side
> - **Novelty:** Mix of familiar + a few novel ideas
> - **Scanning:** by separate hardware that sends data of tool being present and checked out to a Firebase Firestore from which the app will be reading


### Handoff to Claude Code

The next step involved clicking the share button within Claude Design and clicking the handoff to Claude Code button.

![sharing the claude design](../../../images/week-15/sharing.jpg)

Then I copy the text shown and paste into Claude Code and let it handle the rest.

![handing off to claude code](../../../images/week-15/handing-off-to-claude.jpg)

### Building the iOS App with Codemagic

Claude generated the entire file structure and asked me to push it to GitHub, and I had pushed it to my personal GitHub repository and used Codemagic to build the IPA file for the iOS app.

![github repository](../../../images/week-15/github-1.jpg)
![github repository](../../../images/week-15/github-2.jpg)

![codemagic build](../../../images/week-15/codemagic-1.jpg)
![codemagic build](../../../images/week-15/codemagic-2.jpg)
![codemagic build](../../../images/week-15/codemagic-3.jpg)
![codemagic build](../../../images/week-15/codemagic-4.jpg)
![codemagic build](../../../images/week-15/codemagic-5.jpg)
![codemagic build](../../../images/week-15/codemagic-6.jpg)

## Hero Shots

{{< rawhtml >}}
<div style="display: flex; flex-wrap: wrap; gap: 12px; justify-content: center; align-items: flex-start; margin: 20px 0;">
  <img src="../../../images/week-15/ios-app-1.jpg" alt="ios app" style="flex: 1 1 0; min-width: 0; max-width: 32%; height: auto; object-fit: contain; border-radius: 8px;" />
  <img src="../../../images/week-15/ios-app-2.jpg" alt="ios app" style="flex: 1 1 0; min-width: 0; max-width: 32%; height: auto; object-fit: contain; border-radius: 8px;" />
  <img src="../../../images/week-15/ios-app-3.jpg" alt="ios app" style="flex: 1 1 0; min-width: 0; max-width: 32%; height: auto; object-fit: contain; border-radius: 8px;" />
</div>
{{< /rawhtml >}}

---

## Reflection

I am very amused by the capabilities of the AI tools that I have used this week. Me being someone from the mechanical engineering background, I have never thought that I would be able to create a software tool or an Android app — not even 1/10 of this scale — but these tools have enabled me to create such things, and I am very keen on discovering what more AI can do after my Fab Academy journey is complete.
