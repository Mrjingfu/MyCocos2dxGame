
**cocos2dx-store Documentation Conventions**
=====================


##Order of Code 

1. SOOMLA Copyright message 
2. Class description
3. Fields
4. Constructors
5. Destructor
6. Public methods
7. Private methods


##SOOMLA's Copyright Message


SOOMLA is licensed under the Apache License. This copyright message must be included at the top of every file.

```
/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

```

##General Guidelines

- Documentation should be written in the header files (.h), and should NOT be repeated in the implementation (.cpp) files. 
- A doc comment must precede a class, method declaration, constructor, or field (more details below).
- For private methods, documentation comments are optional - if the method is non-trivial and complex, you should document it, otherwise leave it with no comments.
- Do not write documentation for trivial getter and setter methods.
- Do not write documentation for trivial fields.
- A doc comment is made up of two parts: a description and `@`tags.
- The first line of a comment MUST begin with the begin-comment delimiter ( /**).
- The last line of a comment MUST end with the end-comment delimiter ( */).
- Limit any doc-comment lines to 80 characters.


##Use of Doxygen

**Common tags to use**

For comments before class declarations:

- `@class [classname]` - provide the class name.
- `@brief [description]` - describe what the class does.

For comments before method declarations:

- `@param [param] [description]` - describe what value this parameter should be.
- `@return [description]` - describe the return value of the method.
- `@see [reference]` - reference related method.
- `@warning [description]` - describe warnings the user should be aware of.
- `@exception [name] [description]` - describe in what situations the exception will be thrown.
- When referring to source code, wrap the code in backtick quotes: \`someCode\`. Doxygen will convert this to `someCode`.
- To refer to another class simply write the name of the class with no tags. Doxygen will recognize the class and turn it into a link.

For more information about Doxygen conventions see http://www.stack.nl/~dimitri/doxygen/manual/commands.html. 

##Description and Tags

**Classes**

- State the purpose of this class.
- Include possible 'Real Game Examples' to make the purpose clearer.
- Include any important notes or warnings the user should know.
- Declare the inheritance path like so: Inheritance: Class > Superclass > …
    - Do not declare an inheritance path that consists of only one level.

Example:

```
/** 
 @class CCSingleUseVG
 @brief A consumable virtual good that can be purchased an unlimited number of times.
     
 Single Use virtual goods are the most common type of `VirtualGood`.
 The `CCSingleUseVG`'s characteristics are:
 1. Can be purchased an unlimited number of times.
 2. Has a balance that is saved in the database. Its balance goes up when
    you `give` it or `buy` it. The balance goes down when you `take` it.
 Real Game Examples: 'Hat', 'Sword', 'Muffin'
 NOTE: In case you want this item to be available for purchase with real $$
    you'll need to define it in the Market (Google Play, App Store, etc...).
     
 Inheritance: SingleUseVG > VirtualGood > PurchasableVirtualItem > 
 VirtualItem
 */
 class CCSingleUseVG : public CCVirtualGood {
    ...
 }
```
<br>
**Methods**

- The description must begin with a 3rd person descriptive verb.
    - CORRECT: “Checks…”, “Converts…”, “Retrieves...”, etc.. 
    - INCORRECT: “Check”, “This method does…” 
    - The description of the method cannot begin with “Returns…”
- Include possible examples to make the purpose of the method clearer.
- Include any important notes or warnings the user should know.
- Overriding methods - if the overriding method’s description is exactly the same as its parent method’s description, write: “see parent”. Otherwise, write a description. 
- If all the functions of a class are overriding methods, write "See parent for all functions." in the class description and nothing in the method descriptions. 

Example:
```
/**
 Retrieves the item id of the current upgrade of the virtual good with
 the given `goodItemId`.
 @param goodItemId Id of the virtual good whose upgrade id we want to
        know. The `goodItemId` can be of any `CCVirtualGood`.
 @param soomlaError A `CCSoomlaError` for error checking.
 @return The upgrade id if exists, or empty string otherwise.
 */
 std::string getGoodCurrentUpgrade(const char *goodItemId, CCSoomlaError **soomlaError);
```

<br>
**Fields**

For non-trivial fields, write a clear description of the variable. 

- If the description fits on the same line as the code, insert it following the code.
- If the comment fits on one line, add a comment above the line of code.
- Otherwise, if the comment is longer than one line, use the regular commenting conventions.

Example:
```
#define TAG "CCSoomlaError" // used for Log error messages

// TAG is used for Log error messages ... more-text more-text more-text more-text...
#define TAG "CCSoomlaError"

/**
 TAG is used for Log error messages ... more-text more-text more-text more-text
 more-text more-text more-text more-text more-text more-text more-text more-text...
 */
#define TAG "CCSoomlaError"
```



    

