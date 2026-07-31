## myStackChan BusDisplay
Displays my favorite bus leaving time.

- A Python script running on my Mac:
  - harvests Annecy's [SIBRA](https://www.sibra.fr) bus network web site using [Selenium](https://www.selenium.dev);
  - sends 'minutes left before departure' to the StackChan over USB using serial communication.
- The StackChan:
  - waits for 'minutes left before departure’;
  - displays them as color-coded buttons, one row at a time.
