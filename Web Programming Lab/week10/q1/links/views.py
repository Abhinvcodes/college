from django.shortcuts import render, redirect, get_object_or_404
from .models import Category, Page
from .forms import CategoryForm, PageForm

def directory_index(request):
    # 1. Handle form submissions to populate the database
    if request.method == 'POST':
        if 'submit_category' in request.POST:
            cat_form = CategoryForm(request.POST)
            if cat_form.is_valid():
                cat_form.save()
                return redirect('directory_index')
                
        elif 'submit_page' in request.POST:
            page_form = PageForm(request.POST)
            if page_form.is_valid():
                page_form.save()
                return redirect('directory_index')

    # 2. Fetch the data to display
    # prefetch_related optimizes the database query when retrieving the nested pages
    categories = Category.objects.prefetch_related('page_set').all()
    
    # 3. Create fresh, empty forms for the template
    cat_form = CategoryForm()
    page_form = PageForm()

    context = {
        'categories': categories,
        'cat_form': cat_form,
        'page_form': page_form,
    }
    return render(request, 'directory.html', context)

def go_to_page(request, page_id):
    # 1. Grab the specific page from the database
    page = get_object_or_404(Page, id=page_id)
    
    # 2. Increment the page views
    page.views += 1
    page.save()
    
    # 3. Increment the category visits at the same time
    category = page.category
    category.visits += 1
    category.save()
    
    # 4. Redirect the user to the actual external URL
    return redirect(page.url)