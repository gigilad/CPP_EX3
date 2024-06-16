תעודת זהות-315284554, gilada8892@gmail.com

קטאן - מחלקות וירושה
"המתיישבים של קטאן" הוא משחק קופסה ל-3 עד 4 שחקנים המשלב חשיבה אסטרטגית, ניהול משאבים ויכולת מסחר. מטרת המשחק היא לצבור ראשון 10 נקודות ניצחון.

היררכיית המחלקות
לפני שאסביר על המימוש, אסקור את המחלקות ואת ההיררכיה שלהן.

מחלקות המשחק:

Building: מחלקה המייצגת מבנה כלשהו בלוח המשחק. המבנה יכול להיות קודקוד או דרך. המחלקה מחזיקה משתנה המצביע על מי שולט על המבנה, המאותחל ל-(-1).

Vertex: מחלקה זו מייצגת קודקוד בלוח. המחלקה יורשת ממחלקת Building. היא מחזיקה את ערכי ה-x וה-y שלו, וקטור של משאבים שהוא יכול לקבל, וקטור של קודקודים שכנים שלו, ווקטור של דרכים המגיעות או יוצאות ממנו.

Road: מחלקה המייצגת דרך בלוח. המחלקה יורשת ממחלקת Building. היא מורכבת משני מצביעים לקודקודים שלה (קודקוד ראשון וקודקוד שני).

Resource: מחלקה המייצגת את סוגי המשאבים האפשריים.

Land: מחלקה המייצגת חלקת אדמה בלוח (משושה). המחלקה מחזיקה את המספר שלה, את סוג המשאב שהיא נותנת, ווקטור של מצביעים לדרכים וקודקודים שהיא מכילה.

Card, DevelopmentCard, ResourceCard: מחלקת Card היא מחלקה בסיסית שממנה יורשות מחלקות קלף פיתוח וקלף משאב. המחלקה מחזיקה מחרוזת המייצגת את סוג הקלף.

Player: מחלקה המייצגת שחקן במשחק. השחקן מחזיק שם, אינדקס, כמות נקודות, כמות קלפי אבירים, וקטור של כרטיסי משאבים ווקטור של כרטיסי פיתוח.

Board: מחלקה המייצגת את לוח המשחק. המחלקה מחזיקה לוח דו-ממדי המורכב מ-19 משושים, ווקטור של מצביעים לכל הדרכים וכל הקודקודים הקיימים בלוח.

Catan: מחלקה המייצגת את המשחק עצמו. המחלקה מחזיקה את לוח המשחק, את השחקנים, ואת קלפי הפיתוח. המצב מאותחל בתחילת המשחק.
                                                                                                                        
מימוש המשחק-

הכנת הלוח והשחקנים

לפני תחילת המשחק נוצר הלוח ונוצרים השחקנים. השחקנים מחזיקים שם ואינדקס (0, 1 או 2) שמייצג אותם, דבר שעוזר בקביעת תור השחקנים ובזיהוי השחקן השולט על חלקה, עיר, יישוב או דרך מסוימת.

יצירת הלוח-

בהתחלה נוצר לוח של מצביעים לקודקודים של המפה ולוח דו-ממדי המורכב ממשושים. נוסחה מסוימת שחקרתי עוזרת למצוא את הקודקוד השמאלי העליון של כל משושה. הפונקציה initLands דואגת לכך שהלוח נוצר באופן רנדומלי בכל משחק, כך שמיקום המשאבים ומספריהם משתנה ממשחק למשחק. בעת יצירת משושה, המצביעים לקודקודים שלו נוספים. אם מצביע כבר קיים (כיוון שמשושים יכולים לשתף קודקודים), מחזירים אותו, אחרת יוצרים מצביע חדש ומוסיפים אותו לוקטור קודקודי הלוח וגם לוקטור קודקודי החלקה. אותה גישה מיושמת לגבי הדרכים.

[ ]   [ ]  [ IRON  11] [ IRON  6] [ IRON  3] 
[ ]    [ WOOL  8] [ DESERT  0] [ BRICK  5] [ WOOL  2] 
[ WOOL  3] [ BRICK  4] [ WOOL  6] [ OATS  5] [ OATS  8] 
    [ WOOD  9] [ WOOD  10] [ BRICK  12] [ OATS  9]  [ ]  
          [ OATS  11] [ WOOD  10] [ WOOD  4]  [ ]   [ ]
          
תחילת המשחק-

כל שחקן מתחיל את המשחק עם מיקום של 2 דרכים ו-2 יישובים, באמצעות קריאה לפונקציות playRoad ו-playSettlement. ב-2 הסיבובים הראשונים, השחקן ממקם את הדרכים והיישובים בצורה חופשית ללא צורך במשאבים. הפונקציות מקבלות וקטור של משאבים ווקטור של מספרים, ומחפשות חלקה בלוח המשחק המכילה מספר מהוקטור המספרים ומשאב מהוקטור המשאבים.

בניית דרך-

הפונקציה playRoad מחפשת דרך פנויה (שהאינדקס השולט עליה היא 1-) שיש לה דרך שכנה בבעלות השחקן או שיש לה בקצוות יישוב/עיר בבעלות השחקן. אם כן, מעדכנים את השליטה בדרך לאינדקס השחקן. אם לא, ממשיכים לחפש חלקות אחרות.

בניית יישוב-

הפונקציה playSettlement פועלת על עיקרון דומה, אך ניתן לבנות יישוב רק על צומת שאליה מובילה דרך אחת לפחות ובמרחק של 2 קטעי דרך מיישוב אחר. כאשר שחקן רוצה לבנות עיר, הוא בודק את המשאבים הנדרשים ובונה את העיר באותו אופן. אם נמצא קודקוד לבנייה, השחקן מקבל נקודה על יישוב ו-2 נקודות על עיר.

הטלת קוביה-

הטלת קוביה נעשית בתורו של כל שחקן. הפונקציה מגרילה מספר בין 2 ל-12. אם יוצא 7, נקרא לפונקציה CutResourceCards הבודקת אם יש לשחקנים יותר מ-7 כרטיסי משאבים ואם כן, מוחקת חצי מהם. אחרת, נקרא לפונקציה handleDice שבודקת את מספרי חלקות המפה ומוסיפה לשחקנים משאבים בהתאם למספר הקוביה.

קניית קלף פיתוח-

קניית קלף פיתוח נעשית רק בתורו של השחקן, ומבוצעת רק אם יש לו את המשאבים המתאימים. הקלף נבחר רנדומלית מתוך וקטור קלפי הפיתוח במחלקת Catan ומתווסף לוקטור קלפי הפיתוח של השחקן,במידה אם יצא לשחקן כרטיס מסוג שנת שפע הוא יכול לקרוא לפונקציה usePlentYear שמקבלת וקטור של 2 משאבים שהשחקן ירצה לקבל ומוסיפה לשחקן את המשאבים האלו.

מסחר-

המשחק מאפשר שתי פונקציות מסחר - tradeResource ו-tradeDevelopmentCards. הפונקציות מאפשרות החלפת משאבים או קלפי פיתוח בין שחקנים. הפונקציות בודקות אם הקלפים קיימים אצל השחקנים, מבצעות את ההחלפה, ומשנה את נקודות השחקנים בהתאם.

סיום תור-

הפונקציה endTurn מעבירה את התור לשחקן הבא. לאחר מכן, מתבצעת בדיקה אם השחקן הבא הגיע ל-10 נקודות וניצח את המשחק.

כמובן שקיימות עוד שיטות שעזרו לי , ניתן לראות בקבצי הקוד.






                                                                                                                           

