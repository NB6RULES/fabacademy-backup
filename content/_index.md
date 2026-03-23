+++
date = '2026-01-22T21:00:00+05:30'
draft = false
title = 'FAB Academy - Nadec Biju'
bookToC = false
+++

<style>
  @import url('https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap');

  .slot-btn-wrap {
    position: relative;
    display: inline-block;
  }

  .slot-btn-wrap::before {
    content: '';
    position: absolute;
    inset: -5px;
    border-radius: 999px;
    border: 1px solid #330011;
    box-shadow: 0 0 6px #ff335811;
    pointer-events: none;
  }

  .slot-btn {
    display: inline-flex;
    align-items: center;
    justify-content: center;
    gap: 0.6em;
    padding: 0.75em 2em;
    border-radius: 999px;
    background: linear-gradient(180deg, #330022 0%, #1a000f 60%, #290018 100%);
    color: #ff3355;
    border: 2px solid #cc0044;
    box-shadow:
      0 0 10px #ff335555,
      0 0 30px #ff335522,
      inset 0 1px 0 #ff335533,
      inset 0 -2px 0 #0a0005;
    font-family: 'Press Start 2P', monospace;
    font-size: 0.6rem;
    letter-spacing: 0.12em;
    text-transform: uppercase;
    text-shadow: 0 0 8px #ff3355cc, 0 0 20px #ff335566;
    cursor: pointer;
    position: relative;
    overflow: hidden;
    transition: box-shadow 0.15s ease, transform 0.1s ease, background 0.15s ease, border-color 0.15s ease;
    outline: none;
    text-decoration: none;
    animation: blink-light 0.6s ease-in-out infinite;
  }

  @keyframes blink-light {
    0%, 100% {
      box-shadow:
        0 0 10px #ff335555,
        0 0 30px #ff335522,
        inset 0 1px 0 #ff335533,
        inset 0 -2px 0 #0a0005;
    }
    50% {
      box-shadow:
        0 0 16px #ff3355aa,
        0 0 48px #ff335544,
        inset 0 1px 0 #ff335555,
        inset 0 -2px 0 #0a0005;
    }
  }

  .slot-btn::before {
    content: '';
    position: absolute;
    top: 0; left: 8%; right: 8%;
    height: 35%;
    border-radius: 999px 999px 60% 60% / 999px 999px 40% 40%;
    background: linear-gradient(180deg, rgba(255,255,255,0.08) 0%, transparent 100%);
    pointer-events: none;
  }

  .slot-btn::after {
    content: '';
    position: absolute;
    top: 0; left: -120%;
    width: 60%; height: 100%;
    background: linear-gradient(105deg, transparent 20%, rgba(255,51,85,0.18) 50%, transparent 80%);
    transform: skewX(-15deg);
    transition: left 0.45s ease;
    pointer-events: none;
  }

  .slot-btn:hover::after { left: 160%; }

  .slot-btn:hover {
    border-color: #ff3355;
    background: linear-gradient(180deg, #440033 0%, #220018 60%, #330022 100%);
    box-shadow:
      0 0 16px #ff3355aa,
      0 0 48px #ff335533,
      inset 0 1px 0 #ff335555,
      inset 0 -2px 0 #0a0005;
    transform: translateY(-3px);
    text-shadow: 0 0 12px #ff3355ff, 0 0 30px #ff335599;
  }

  .slot-btn:active {
    transform: translateY(1px) scale(0.97);
    box-shadow:
      0 0 6px #ff335544,
      inset 0 2px 6px rgba(0,0,0,0.5),
      inset 0 -1px 0 #0a0005;
    background: linear-gradient(180deg, #1a000f 0%, #120008 60%, #1a000f 100%);
  }

  .slot-btn:focus-visible {
    outline: 2px solid #ff3355;
    outline-offset: 4px;
  }

  .home-mini {
    display: grid;
    grid-template-columns: repeat(3, 1fr);
    gap: 0.6rem;
    align-items: center;
  }

  .slot-btn-wrap {
    flex-grow: 0;
  }

  .home-hero {
    margin-bottom: 0.5rem;
  }

  .home-grid {
    margin-top: 0.5rem;
  }
</style>

<div class="home">
  <section class="home-hero">
    <div class="home-hero__inner">
      <div class="home-copy">
        <p class="home-kicker">FAB Academy 2026 &bull; Kochi</p>
        <h1 class="home-title">Nadec's Fab Academy Journey</h1>
        <p class="home-tagline">Mechanical Engineering student turning ideas into reality through digital fabrication, CAD, and robotics.</p>
      </div>
      <div class="home-media">
        <a class="home-photo" href="docs/about-me/">
          <img src="images/about-me/dp.jpeg" alt="Nadec Biju" loading="eager" decoding="async">
        </a>
        <div class="home-mini">
          <a class="home-mini-card home-mini-card--now" href="docs/assignment/week-8/">Now: Week 08</a>
          <a class="home-mini-card home-mini-card--agreement" href="docs/agreement/">Student Agreement</a>
          <a class="home-mini-card home-mini-card--cool" href="docs/assignment/week-3/laser-gauge-tool/">Laser Gauge Tool</a>
          <a class="home-mini-card home-mini-card--cool" href="docs/assignment/week-3/#glasses">Neil Statue</a>
          <div class="slot-btn-wrap">
            <a href="docs/assignment/week-4/nb6-boy/" class="slot-btn">NB6boy Scores</a>
          </div>
        </div>
      </div>
    </div>
  </section>
  <section class="home-grid" aria-label="Quick links">
    <a class="home-card" href="docs/assignment/">
      <div class="home-card__title">Weekly Assignments</div>
      <div class="home-card__meta">Documentation + weekly builds</div>
    </a>
    <a class="home-card" href="docs/final-project/">
      <div class="home-card__title">Final Project</div>
      <div class="home-card__meta">Idea, planning, and progress</div>
    </a>
    <a class="home-card" href="docs/about-me/">
      <div class="home-card__title">About Me</div>
      <div class="home-card__meta">Experience + projects</div>
    </a>
  </section>
  <section class="home-strip" aria-label="Start here">
    <div class="home-strip__left">
      <strong>Start here:</strong> I recommend Week 01 if you're new to my workflow.
    </div>
    <div class="home-strip__right">
      <a class="home-strip__link" href="docs/assignment/week-1/">Go to Week 01 &rarr;</a>
    </div>
  </section>
</div>

