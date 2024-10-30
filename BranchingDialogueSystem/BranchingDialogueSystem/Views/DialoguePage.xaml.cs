using BranchingDialogueSystem.Models;
using Microsoft.Maui.Controls.PlatformConfiguration;
using System.Text.Json;

namespace BranchingDialogueSystem.Views;

public partial class DialoguePage : ContentPage
{
	public DialoguePage()
    {
        InitializeComponent();
        //DialogueNode Root = JsonSerializer.Deserialize<DialogueNode>(jsonString);
        string Filename = "D:\\UCA\\AdvancedProgramming2024\\BranchingDialogueSystem\\BranchingDialogueSystem\\Resources\\Dialogues\\DialogueJSON.txt";
        if (File.Exists(Filename))
        {
            string DialogueJson = File.ReadAllText(Filename);
            DialogueNode Root = JsonSerializer.Deserialize<DialogueNode>(DialogueJson);

            /*
            DialogueNode DefaultDialogueNode = new DialogueNode();
            DialogueNode Variant1Node = new DialogueNode();
            Variant1Node.DialogueText = "Zalupa";
            DialogueNode Variant2Node = new DialogueNode();
            string AppDataPath = Directory.GetCurrentDirectory();
            Variant2Node.DialogueText = AppDataPath;

            DefaultDialogueNode.DialogueChoiceTexts.Add("Variant 1");
            DefaultDialogueNode.DialogueChoiceNodes.Add(Variant1Node);
            DefaultDialogueNode.DialogueChoiceTexts.Add("Variant 2");
            DefaultDialogueNode.DialogueChoiceNodes.Add(Variant2Node);
            DefaultDialogueNode.DialogueText = "Default text";
            */


            DisplayDialogue(Root);

        }


       
    

        
        
        
		
	}

	private void DisplayDialogue(DialogueNode NewDialogueNode)
	{
        string serialized = JsonSerializer.Serialize(NewDialogueNode);
        BindingContext = NewDialogueNode;
	}

	private async void OnDialogueOptionChosen(object sender, EventArgs e)
	{
		await ((Button)sender).ScaleTo(0.9, 150);
		await ((Button)sender).ScaleTo(1, 150);

		string ButtonText = ((Button)sender).Text;
		for (int i = 0; i < ((DialogueNode)BindingContext).DialogueChoiceTexts.Count; ++i)
		{
			if (((DialogueNode)BindingContext).DialogueChoiceTexts[i] == ButtonText)
			{
				if (i < ((DialogueNode)BindingContext).DialogueChoiceNodes.Count)
				{
                    DisplayDialogue(((DialogueNode)BindingContext).DialogueChoiceNodes[i]);
                }
				
			}
		}

        return;
	}
}