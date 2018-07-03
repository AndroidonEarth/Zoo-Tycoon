# Zoo Tycoon
Zoo Tycoon concept game written in C++

## Gameplay

The player begins with a specific amount of money in the bank, e.g. 100,000 dollars. At the start, the player needs to buy three types of animals (tigers, penguins, turtles) to start the business. Each type should have a quantity of either 1 or 2. For each animal bought, the cost is subtracted from the bank. All newly bought animals are 1 day old.

Each turn is a “day”. At the beginning of the day, all animals increase age by 1 day, and the player needs to pay the feeding cost of each animal. Feeding is required so the animals don’t die. After the feeding cost is subtracted from the bank, one randomized event takes place during the day from the following list:

1. **A sickness occurs to an animal in the zoo:**
An animal of a random type will die and be removed from the zoo.
2. **A boom in zoo attendance occurs:**
Generates a random bonus for the day, e.g 250-500 dollars for each tiger in the zoo, and adds the bonus payoff for each tiger to the total payoff of the day as a reward.
3. **A baby animal is born:**
An animal of a random type has a baby if there is an animal of that type old enough to be a parent (age >= 3), and adds babies to the zoo depending on the “number of babies” specific to the type of animal. Baby animals start at age 0.
4. **Nothing happens**


After the random event, profits are calculated for the day based on the number of each animals and their payoff. If there is a bonus for the 
day, add it to the profit as well. Before the day ends, asks the player if they would like to buy an adult animal. If they do, asks for the type of animal they would like, then adds the animal to the zoo and subtracts that cost from the bank. The adult animal that is bought will be 3 days old.

After the end of a day, the game prompts the player whether to keep playing or end the game. **If the player has no money, the game is over.**
