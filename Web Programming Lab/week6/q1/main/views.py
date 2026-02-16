from django.shortcuts import render

def calculator(request):
    result = None
    num1 = request.POST.get('num1')
    num2 = request.POST.get('num2')
    operation = request.POST.get('operation')

    if request.method == 'POST':
        try:
            n1 = int(num1)
            n2 = int(num2)
            
            if operation == 'add':
                result = n1 + n2
            elif operation == 'subtract':
                result = n1 - n2
            elif operation == 'multiply':
                result = n1 * n2
            elif operation == 'divide':
                result = n1 / n2 if n2 != 0 else "Error (Div by 0)"
        except (ValueError, TypeError):
            result = "Please enter valid integers"

    return render(request, 'calculator.html', {'result': result})