# Spellbook Search

**Advanced Programming**

**Dmitrii Kolchin**  
**2220982**

---
## Research  

The implementation of this task required focusing on two primary areas:  
1. **Dynamic Programming and Levenshtein Distance**: To address the problem, I revisited the concept of dynamic programming algorithms. Inspired by Aimar's suggestion, I utilised the Levenshtein distance [(Introduction to Levenshtein distance - GeeksforGeeks, s.d.)](https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/) distance to enable search results to display close variants of a query.  
2. **Hosting a Web App**: I explored using the PythonAnywhere service to host a web application. This approach allowed me to store a JSON file containing all the spells and fetch it dynamically in C#. This method eliminated the need for hardcoding the spells, as required in the initial task, and avoided issues associated with reading local files.  

---

## Implementation  

### Calculating the Levenshtein Distance  

I implemented a function to calculate the Levenshtein distance [(Introduction to Levenshtein distance - GeeksforGeeks, s.d.)](https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/) between two strings. This was achieved using the Wagner-Fischer algorithm [(Gaddam, 2024)](https://medium.com/@yasaswini.gaddam21/wagner-fischer-algorithm-minimum-edit-distance-4e61bba9b656), a dynamic programming-based approach.  

The algorithm utilises a `Distances[][]` array where `Distances[i][j]` represents the Levenshtein distance between the first *i* characters of the first string and the first *j* characters of the second string. The array is populated as follows:  
- **Base cases**:  
  - If `i = 0`, then `Distances[i][j] = j` (removing *j* characters).  
  - If `j = 0`, then `Distances[i][j] = i` (adding *i* characters).  
- **Recursive step**:  
  - If `str[i] == str[j]`, then `Distances[i][j] = Distances[i-1][j-1]` (no edits needed for the last character).  
  - Otherwise:  
    ```plaintext
    Distances[i][j] = min(
      Distances[i-1][j-1] + 1, // Swap last character
      Distances[i-1][j] + 1,  // Remove one character
      Distances[i][j-1] + 1   // Add one character
    )
    ```  
The final Levenshtein distance is stored in `Distances[n][m]`, where *n* and *m* are the lengths of the two strings.  

The implementation in C# is as follows:  
```cs
static int LevenshteinDistance(string left, string right)
    {
        // Create a 2D array to store the distances
        List<List<int>> distances = new List<List<int>>();
        for (int i = 0; i <= left.Length; ++i)
        {
            distances.Add(new List<int>());
            for (int j = 0; j <= right.Length; ++j)
            {
                distances[i].Add(0);
            }
        }

        // Initialize the first row and column
        for (int i = 0; i <= left.Length; ++i)
        {
            distances[i][0] = i;
        }

        for (int j = 0; j <= right.Length; ++j)
        {
            distances[0][j] = j;
        }

        // Filling the dynamic array
        for (int i = 1; i <= left.Length; ++i)
        {
            for (int j = 1; j <= right.Length; ++j)
            {
                if (left[i - 1] == right[j - 1])
                {
                    distances[i][j] = distances[i - 1][j - 1];
                }
                else
                {
                    distances[i][j] = 1 + Math.Min(
                        distances[i - 1][j],
                        Math.Min(
                            distances[i][j - 1],
                            distances[i - 1][j - 1]
                        ));
                }
            }
        }

        return distances[left.Length][right.Length];
    } 
```  
*Figure 1. Levenshtein distance calculation implemented*

### Searching Spells  

To determine whether a spell matches the search query, I compared its `Name`, `Target`, and `Type` against the query. 
For flexibility, I implemented a method that retrieves all searchable fields for a spell.
 This ensures that changes to the list of parameters can be easily managed:  
```cs
 public string[] GetAllSearchableFields()
    {
        return new string[] {Name, Target.ToString(), Type.ToString()};
    }
```
*Figure 2. Function that returns an arrya of all spell fields that can be searched*
Using this, I iterated through the array of spells, retrieved their associated keywords, and compared them to the query, with a maximum Levenshtein distance of 2:  
```cs
 public static List<Spell> SearchSpells(List<Spell> spellList, string keyword)
    {
        List<Spell> results = new List<Spell>();

        // Student solution should be placed here:
        // Implement a search algorithm (e.g., linear search, binary search)
        // Print all spells
        foreach (var spell in spellList)
        {
            string[] spellSearchableFields = spell.GetAllSearchableFields();
            foreach (var spellKeyword in spellSearchableFields)
            {
                if (LevenshteinDistance(spellKeyword, keyword) <= MaxLevenshteinDistance)
                {
                    results.Add(spell);
                    break;
                }
            }


        }

        return results;
    }
```
*Figure 3. Search logic*

### Hosting JSON on PythonAnywhere  

To host the spell data, I converted the `CreateSpells` function output to JSON format. The resulting JSON structure is as follows:  
```json
{
    "Name": "Fireball",
    "ManaCost": 50,
    "Power": 100,
    "Target": "SingleTarget",
    "Type": "Damage"
}
```  
*Figure 4. JSON entry for a "Fireball" spell*

I then created a Flask-based web application hosted on PythonAnywhere, with the following code:  
```py
from flask import Flask, jsonify
import json

app = Flask(__name__)

@app.route('/')
def get_spell_list():
    with open('SpellList.json', 'r') as file:
        data = json.load(file)
    return jsonify(data)
```  
*Figure 5. Flask app code*

The web app is accessible at [https://pazhilayazhaba.pythonanywhere.com/](https://pazhilayazhaba.pythonanywhere.com/).  

In C#, I implemented HTTP response handling to fetch the spells dynamically. If the JSON file could not be accessed, the program falls back to the original `CreateSpells()` method:  
```cs
string jsonData = "";
using (HttpClient client = new HttpClient())
{
    // Replace with your actual PythonAnywhere URL
    string url = "https://pazhilayazhaba.pythonanywhere.com/";
    HttpResponseMessage response = await client.GetAsync(url);
    response.EnsureSuccessStatusCode();  // Ensure we got a successful response
    jsonData = await response.Content.ReadAsStringAsync();
}

List<Spell>? spells = null;

if (jsonData.Length > 0)
{
    spells = JsonSerializer.Deserialize<List<Spell>>(jsonData);
}

spells ??= CreateSpells();
```  
*Figure 6. Reading spells JSON from the hosted web application*
All the source files can be obtained [here](https://github.com/DmitryKolchin/AdvancedProgramming2024/tree/main/SpellbookSearch)

---

## Critical Reflection  

### What Went Well  
- Successfully refreshed my knowledge of dynamic programming and Levenshtein distance.  
- Gained additional experience with C#.  
- Deployed my first web app on PythonAnywhere using Flask.  

### Areas for Improvement  
- Need to deepen my understanding of C#; I relied on ChatGPT for some basic tasks, such as making HTTP requests.  
- Need to improve my knowledge of Flask for more robust web application development.  

---  

## Bibliography
- Gaddam, Y. (2024) Wagner–Fischer algorithm: Minimum Edit Distance. At: https://medium.com/@yasaswini.gaddam21/wagner-fischer-algorithm-minimum-edit-distance-4e61bba9b656 (Accessed  04/12/2024).
- Introduction to Levenshtein distance - GeeksforGeeks (s.d.) At: https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/ (Accessed  04/12/2024).
- PythonAnywere (2015) The PythonAnywhere help pages. At: https://help.pythonanywhere.com/pages/ (Accessed  30/11/2024).
- Rick-Anderson (s.d.) HttpResponse Class (System.Web). At: https://learn.microsoft.com/en-us/dotnet/api/system.web.httpresponse?view=netframework-4.8.1 (Accessed  30/11/2024).
- Welcome to Flask — Flask Documentation (3.1.x) (s.d.) At: https://flask.palletsprojects.com/en/stable/ (Accessed  30/11/2024).

## Declared Assets

The following assets were created or modified with the use of GPT 4o:
```md 
- DevelopmentJournal.md
- SpellList.json
- flask_app.py
```