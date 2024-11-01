using BranchingDialogueSystem.Models;
using Microsoft.Maui.Controls.PlatformConfiguration;
using System.Text.Json;

namespace BranchingDialogueSystem.Views;

public partial class DialoguePage : ContentPage
{
	public DialoguePage()
    {
        InitializeComponent();

        string Filename = "D:\\UCA\\AdvancedProgramming2024\\BranchingDialogueSystem\\BranchingDialogueSystem\\Resources\\Dialogues\\DialogueJSON.txt";
        if (File.Exists(Filename))
        {
            string DialogueJson = File.ReadAllText(Filename);

			if (DialogueJson == null)
			{
				return;
			}

            DialogueNode Root = JsonSerializer.Deserialize<DialogueNode>(DialogueJson);

			if (Root == null)
			{
				return;
			}

            DisplayDialogue(Root);
        }
	}

	private void DisplayDialogue(DialogueNode NewDialogueNode)
	{
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