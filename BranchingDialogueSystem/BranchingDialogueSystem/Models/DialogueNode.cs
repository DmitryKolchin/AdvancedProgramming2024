using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace BranchingDialogueSystem.Models;

[JsonConverter(typeof(JsonStringEnumConverter))]
internal enum DialogueNodeStatus
{
    Success,
    Failure,
    Neutral,
    Default
}

internal class DialogueNode
{
    public string DialogueText { get; set; } = string.Empty;

    public DialogueNodeStatus Status { get; set; }

    public ObservableCollection<string> DialogueChoiceTexts { get; set; } = [];
    public ObservableCollection<DialogueNode> DialogueChoiceNodes { get; set; } = [];

}
