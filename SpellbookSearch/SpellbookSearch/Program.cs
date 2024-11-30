// See https://aka.ms/new-console-template for more information
using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;


// Define the target types
[JsonConverter(typeof(JsonStringEnumConverter))]
public enum TargetType
{
    SingleTarget,
    AOE,
    Self
}

// Define the spell types
[JsonConverter(typeof(JsonStringEnumConverter))]
public enum SpellType
{
    Damage,
    Heal,
    Buff,
    Debuff
}

// The Spell class represents a single spell with attributes
public class Spell(string name, int manaCost, int power, TargetType target, SpellType type)
{
    public string Name { get; set; } = name;
    public int ManaCost { get; set; } = manaCost;
    public int Power { get; set; } = power;
    public TargetType Target { get; set; } = target;
    public SpellType Type { get; set; } = type;

    // Method to print spell details
    public void PrintSpell()
    {
        Console.WriteLine($"Name: {Name}, Mana Cost: {ManaCost}, Power: {Power}, Target: {Target}, Type: {Type}");
    }

    public string[] GetAllSearchableFields()
    {
        return new string[] {Name, Target.ToString(), Type.ToString()};
    }
}

public class Program
{
    private static int MaxLevenshteinDistance { get; set; } = 2;
    // Implementing the Wagner-Fischer algorithm for calculating the Levenshtein distance
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

    // Create a list of spells with the attributes
    public static List<Spell> CreateSpells()
    {
        return new List<Spell>
        {
            new Spell("Fireball", 50, 100, TargetType.SingleTarget, SpellType.Damage)
        };
    }

    // Task for student: Implement a search function to find spells based on keywords
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



    static async Task Main(string[] args)
    {
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



        Console.WriteLine("Search terms: Damage, Heal, Buff, Debuff, SingleTarget, AOE, Self");
        Console.WriteLine("Enter a search keyword:");
        string keyword = Console.ReadLine();

        // Search for spells based on the keyword
        List<Spell> matchingSpells = SearchSpells(spells, keyword);

        // Display the results
        if (matchingSpells.Count > 0)
        {
            Console.WriteLine("Matching Spells:");
            foreach (var spell in matchingSpells)
            {
                spell.PrintSpell();
            }
        }
        else
        {
            Console.WriteLine("No spells matched the search criteria.");
        }
    }
}