using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BranchingDialogueSystem.Models;

internal class StatusTextBehavior : Behavior<Label>
{
    protected override void OnAttachedTo(Label bindable)
    {
        base.OnAttachedTo(bindable);
        bindable.BindingContextChanged += OnBindingContextChanged;
    }

    protected override void OnDetachingFrom(Label bindable)
    {
        base.OnDetachingFrom(bindable);
        bindable.BindingContextChanged -= OnBindingContextChanged;
    }

    private void OnBindingContextChanged(object sender, EventArgs e)
    {
        var label = (Label)sender;
        if (label.BindingContext is DialogueNode dialogue)
        {
            if (dialogue.Status == DialogueNodeStatus.Default)
            {
                label.IsVisible = false;
                return;
            }

            Color NewTextColor = new Color();
            switch (dialogue.Status)
            {
                case DialogueNodeStatus.Success:
                    NewTextColor = Colors.Green;
                    break;
                case DialogueNodeStatus.Neutral:
                    NewTextColor = Colors.Yellow;
                    break;
                case DialogueNodeStatus.Failure:
                    NewTextColor = Colors.Red;
                    break;
                default:
                    NewTextColor = Colors.Black;
                    break;
            }
            label.IsVisible = true;
            label.TextColor = NewTextColor;
            label.Text = dialogue.Status.ToString() + ": ";

        }
    }
}
