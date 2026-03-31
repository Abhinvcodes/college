from django.shortcuts import render
from .models import PollResult

def vote_view(request):
    # Retrieve the poll record, or create it if it doesn't exist yet (id=1)
    poll, created = PollResult.objects.get_or_create(id=1)
    
    context = {
        'voted': False
    }

    if request.method == 'POST':
        # Get the user's choice from the radio buttons
        choice = request.POST.get('choice')
        
        # Increment the correct database field
        if choice == 'good':
            poll.good_votes += 1
        elif choice == 'satisfactory':
            poll.satisfactory_votes += 1
        elif choice == 'bad':
            poll.bad_votes += 1
        
        poll.save() # Save the new tally to the database

        # Calculate percentages
        total_votes = poll.good_votes + poll.satisfactory_votes + poll.bad_votes
        if total_votes > 0:
            context['good_pct'] = round((poll.good_votes / total_votes) * 100)
            context['sat_pct'] = round((poll.satisfactory_votes / total_votes) * 100)
            context['bad_pct'] = round((poll.bad_votes / total_votes) * 100)
        
        # Update context to show results in the template
        context['voted'] = True
        context['selected_choice'] = choice

    return render(request, 'poll/vote.html', context)