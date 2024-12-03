# Educational Game Plan

**Advanced Programming**

**Dmitrii Kolchin**  
**2220982**


## Research

Despite not having ClickUp amongst the provided options in the task, I still decided to use it due to the following facts:
- It was mentioned equally amongst the biased ratings of other task tracker software sites, like Teamhub [(Ansar, 2024)](https://teamhub.com/blog/best-project-management-tools-for-game-developers/), Placky [(7 Best Project Management Tools for Game Development, 2022)](https://plaky.com/blog/game-project-management/), Codecks [(8 Best Project Management Tools for Game Development (The Ultimate List), s.d.)](https://www.codecks.io/blog/project-management-tools-in-game-development/), and sites, that look more or less indepedndent, like [DPM](https://www.codecks.io/blog/project-management-tools-in-game-development/) also mention it. All of them underline ClickUp's ability to view taks both as Kanban board or as a task list, as well as the overall high level of customisation - custom fields, colorful themes, etc.
- Me personally like it more than any other alternative (which is a little bit subjective), and I had experience with Trello, 
You Track and Jira in both professional and personal organisation routine. ClickUp provides the capabilities of in-place time
 tracking (for instance, I am tracking me doing the development journal now in ClickUp) which I find very convinient. It
  is connected to my phone app so I can check updates on my tasks and plan the day on the go. I am quite sure that no else
   students gonna use it. Plus, it provides the ability to embed tasks and lists, like this:
<iframe class="clickup-embed" src="https://sharing.clickup.com/9015630444/t/h/86c0ebvxh/0B4VGPT0LRI6UW0"
 onwheel="" width="100%" height="700px" style="background: transparent; border: 1px solid #ccc;"></iframe>

*Figure 1. My own task in ClickUp* 

## Implementation

Given that we have a clear end goal, fully planned systems, and a comprehensive design document, I decided that the **Waterfall methodology** is the most suitable approach for this project. This methodology is a great fit because the requirements are unlikely to change, and it allows us to proceed in a structured, phase-by-phase manner. It also provides a great focus on testing and polishing [(Waterfall Model - Software Engineering, 2018)](https://www.geeksforgeeks.org/waterfall-model/) Below is an overview of the tasks, distributed across weeks, along with a detailed breakdown of the rationale behind the allocations.

### Project Timeline

Here is the Gantt diagram illustrating the weekly task distribution:
<iframe class="clickup-embed" src="https://sharing.clickup.com/9015630444/g/h/8cnz6kc-195/532d43ffd8bc1ce" onwheel="" width="100%" height="700px" style="background: transparent; border: 1px solid #ccc;"></iframe>

*Figure 2. Gantt diagram* 

---

### Task Allocation and Weekly Breakdown

#### **Week 1**  
- **Core Gameplay (My Task):**  
  I took ownership of developing the core gameplay as it is the foundation of the project. Since the core gameplay is independent of other modules, it allows us to integrate UI and dialogue systems seamlessly later.  
  - *Rationale:* High priority and critical for establishing game mechanics early on.

- **Dialogue System (Developer 1):**  
  Developer 1 is responsible for the dialogue system, designed to function independently of other modules.  
  - *Advantages:*  
    1. Low coupling improves modularity and simplifies debugging.  
    2. Can be reused as a library in future projects.  

- **User Interface (Developer 2):**  
  Developer 2 starts with the generic UI functionality, focusing on placeholders to simulate interactions with gameplay and dialogue systems.  
  - *Rationale:* Placeholder-based implementation avoids blocking and allows parallel development.

---

#### **Week 2**  
- **Progress Update:**  
  - I complete the core gameplay module.  
  - Developer 1 continues with the dialogue system.  
  - Developer 2 continues generic UI development.

---

#### **Week 3**  
- **Progression System (My Task):**  
  I begin work on the progression system, building on the completed core gameplay. While coupling increases slightly due to time constraints, this approach streamlines integration and avoids unnecessary abstraction.  
  - *Blocking Dependency:* Core gameplay must be complete to ensure compatibility.  

- Developer 1 and Developer 2 continue their respective tasks.

---

#### **Week 4**  
- **Collaboration:**  
  - I finish the progression system and collaborate with Developer 2 to integrate UI with gameplay functionality.  
  - Developer 1 wraps up the dialogue system.  

---

#### **Week 5**  
- **Merging and Localization:**  
  - The dialogue system is merged with gameplay, requiring close collaboration between Developer 1 and Developer 2.  
  - Developer 1 begins work on localization, preparing for multi-language support.  
  - I start on the rewards system.  

---

#### **Week 6**  
- **Finalising Modules:**  
  - I complete the rewards system.  
  - Developer 1 finishes localization and continues merging dialogues with UI, factoring in localization.  
  - Developer 2 begins integrating sound effects and animations.

---

#### **Week 7**  
- **Polishing Phase:**  
  - I focus on polishing the gameplay and progression systems.  
  - Developer 1 addresses polishing needs for localization and dialogues.  
  - Developer 2 completes animations and sound effects.

---

#### **Week 8**  
- **Final Polishing:**  
  The entire team dedicates this week to refining the project for a polished final product.

---

### Critical Reflection

#### **What Went Well**  
1. **Tool Efficiency:**  
   ClickUp proved to be a highly convenient and effective tool for task management and planning.  
2. **Clarity of Scope:**  
   The range of tasks and clear design documentation allowed for straightforward planning and prioritisation.

#### **Room for Improvement**  
1. **Time Constraints:**  
   The timeline was tight, making it challenging to incorporate all functionalities.  
2. **Potential Improvements for Future Projects:**  
   - Exploring alternative methodologies like Agile or hybrid approaches for better adaptability.  
   - Considering additional tools or software for improved collaboration and monitoring.

#### **Key Takeaways**  
- By following a structured Waterfall approach, we are likely to deliver a polished product, even if some functionality may remain unimplemented.  
- The dialogue system's modular design ensures it can be reused and enhanced for future projects, making it a valuable asset beyond this project.

---

## Bibliography

- 7 Best Project Management Tools for Game Development (2022) At: https://plaky.com/blog/game-project-management/ (Accessed  03/12/2024).
- 8 Best Project Management Tools for Game Development (The Ultimate List) (s.d.) At: https://www.codecks.io/blog/project-management-tools-in-game-development/ (Accessed  03/12/2024).
- Ansar (2024) 8 Best Project Management Tools for Game Developers. At: https://teamhub.com/blog/best-project-management-tools-for-game-developers/ (Accessed  03/12/2024).
- Manager, T. D. P. (s.d.) 15 Best Project Management Software Picked For 2024. At: https://thedigitalprojectmanager.com/tools/best-project-management-software/ (Accessed  03/12/2024).
- Waterfall Model - Software Engineering (2018) At: https://www.geeksforgeeks.org/waterfall-model/ (Accessed  03/12/2024).


## Declared Assets
Assets made with AI:
- DevelopmentJournal.md