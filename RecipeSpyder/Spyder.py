import re
import requests
import json
from bs4 import BeautifulSoup
from enum import Enum

s_url = "https://satisfactory-calculator.com/en/items"

class RecipeType(Enum):
    Norm = "Recipes"
    Alt = "Alternate recipes"

def ItemHtml(path:str, url:str=s_url, write:bool=False) -> str:
    item_html = requests.get(url)
    if write:
        with open(path, "w") as f:
            f.write(item_html.text)
    return item_html.text

def ItemList(path:str, url:str=s_url, write:bool=False) -> list[str]:
    soup = BeautifulSoup(requests.get(url).text, features="html.parser")
    r = []
    for s in soup.find_all(name="strong")[:-2]:
        r.append(s.text)
    if write:
        with open(path, "w") as f:
            for name in r:
                f.write(name)
                f.write(',')
    return r

def ItemListSelective(path:str, type:str=None, url:str=s_url, write:bool=False) -> list[str]:
    if (type==None):
        return ItemList(path, url, write)
    soup = BeautifulSoup(requests.get(url).text, features="html.parser")
    r = []
    return

def ItemUrl(path:str="Recipe Spyder/local/item_url.txt", url:str=s_url, write:bool=False) -> list[str]:
    soup = BeautifulSoup(requests.get(url).text, features="html.parser")
    strong = soup.find_all("strong")[:-2]
    r = []
    with open(path, "w") as f:
        for s in strong:
            item_url = s.parent.get("href")
            r.append(item_url)
            if write:
                f.write(item_url)
                f.write(",")    

    return r

def ItemRecipe(url:str, f, type:RecipeType, write:bool=False) -> list[list[dict]]:
    result = []
    soup = BeautifulSoup(requests.get(url).text,features="html.parser")
    locate = soup.find("strong", text=type.value) # identify the location of normal recipes, could be None for some item
    if locate != None:
        recipes = locate.parent.parent.parent.parent
    else:
        return result
    recipes_list = recipes.find_all(class_="card-body border-top") # the list of recipes of that given item
    for recipe in recipes_list: # locate the name, value of output, input
        recipe_info = recipe.find_all(class_="row align-items-center")[-1].find_all(class_="col-6") # contains inp and outp
        recipe_input_dict = {} # result would be in it
        recipe_output_dict = {} # result would be in it
        recipe_result = []
        pat = re.compile("\(.*\)(\d*.\d*)(x|m³)\s(([a-z]|\s|-)*)", re.I)

        input = recipe_info[0]
        for item in input.children:
            # item text looks like: (120 / min)12x Bauxite
            # group 1: val, group 3: name
            
            mat_obj = pat.match(item.text)
            recipe_input_dict[mat_obj.group(3)] = float(mat_obj.group(1))
        if write:
            json.dump(recipe_input_dict, f)
            f.write(",")

        output = recipe_info[1]
        for item in output.children:
            
            mat_obj = pat.match(item.text)
            recipe_output_dict[mat_obj.group(3)] = float(mat_obj.group(1))
        if write:
            json.dump(recipe_output_dict, f)
            f.write('\n')

        recipe_result.append(recipe_input_dict)
        recipe_result.append(recipe_output_dict)    
        result.append(recipe_result)
    return result

def AllRecipes(item_url:str="Recipe Spyder/local/item_url.txt", path:str="Recipe Spyder/local/recipe.txt", write:bool=False) -> list[list[dict]]:
    result = []
    with open(path, "w") as f:
        for raw_url in ItemUrl():
            url = MakeUrl(raw_url)
            print(url)
            result += ItemRecipe(url, f, RecipeType.Norm,write=write)
            result += ItemRecipe(url, f, RecipeType.Alt,write=write)
    return result

def DeleteDuplicates(recipes_list:list[list[dict]], path:str="Recipe Spyder/local/recipe_parsed.txt",write:bool=False) -> list[list[dict]]:
    result = []
    for recipe in recipes_list:
        if recipe not in result and recipe[0] != recipe[1]:   
            result.append(recipe)
        else:
            print("duplicates found")
    if write:
        with open(path, "w") as f:
            for r in result:
                json.dump(r[0], f)
                f.write(',')
                json.dump(r[1], f)
                f.write('\n')
    return result

def MakeUrl(url:str, base_url:str = "https://satisfactory-calculator.com") -> str:
    return (base_url + url)


# soup = BeautifulSoup(requests.get("https://satisfactory-calculator.com/en/items/detail/id/Desc_Cement_C/name/Concrete").text,features="html.parser")
# print(soup.find("strong", text="Recipes").parent.parent.parent.parent.find(class_="card-body border-top").find("span").parent.text)

silica_url = "https://satisfactory-calculator.com/en/items/detail/id/Desc_Silica_C/name/Silica"
water = "https://satisfactory-calculator.com/en/items/detail/id/Desc_Water_C/name/Water"
# with open("Recipe Spyder/local/recipe.txt", "w") as f:
#     ItemRecipe(water, f, RecipeType.Norm)
# print(type(AllRecipes()))
if (__name__ == "__main__"):
    # print(DeleteDuplicates(AllRecipes(write=True), write=True))
    soup = BeautifulSoup(requests.get(s_url).text, features="html.parser")
    tag = soup.find(name="main").find(name="nav").find_all(class_="breadcrumb-item")[1]
    print(tag.text)
# ItemUrl(write=True)