import random
import string
from django.shortcuts import render

def generate_captcha():
    # Generates a random 6-character alphanumeric string
    return ''.join(random.choices(string.ascii_uppercase + string.digits, k=6))

def captcha_view(request):
    # Initialize session variables if they don't exist
    if 'captcha_text' not in request.session:
        request.session['captcha_text'] = generate_captcha()
    if 'fail_count' not in request.session:
        request.session['fail_count'] = 0
    
    

    message = ""
    is_disabled = request.session['fail_count'] >= 3

    if request.method == "POST" and not is_disabled:
        user_input = request.POST.get('captcha_input', '').strip()
        correct_captcha = request.session.get('captcha_text')

        if user_input == correct_captcha:
            message = "✅ Success! Captcha Matched."
            # Reset on success
            request.session['fail_count'] = 0
            request.session['captcha_text'] = generate_captcha()
        else:
            request.session['fail_count'] += 1
            message = f"❌ Mismatch. Attempts: {request.session['fail_count']}/3"
            # Refresh captcha on failure
            request.session['captcha_text'] = generate_captcha()
            
            if request.session['fail_count'] >= 3:
                is_disabled = True
                message = "🚫 Account Locked: Too many failed attempts."

    return render(request, 'captcha_app/index.html', {
        'captcha_text': request.session.get('captcha_text'),
        'message': message,
        'is_disabled': is_disabled
    })