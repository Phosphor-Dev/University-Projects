// Generated from crux\pt\Crux.g4 by ANTLR 4.7.2
package crux.pt;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CruxLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		AND=1, OR=2, NOT=3, IF=4, ELSE=5, FOR=6, BREAK=7, TRUE=8, FALSE=9, RETURN=10, 
		SEMICOLON=11, OPEN_PAREN=12, CLOSE_PAREN=13, OPEN_BRACE=14, CLOSE_BRACE=15, 
		OPEN_BRACKET=16, CLOSE_BRACKET=17, ADD=18, SUB=19, MUL=20, DIV=21, GREATER_EQUAL=22, 
		LESSER_EQUAL=23, NOT_EQUAL=24, EQUAL=25, GREATER_THAN=26, LESS_THAN=27, 
		ASSIGN=28, COMMA=29, COMMENT=30, WHITESPACES=31, INTEGER=32, IDENTIFIER=33;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"AND", "OR", "NOT", "IF", "ELSE", "FOR", "BREAK", "TRUE", "FALSE", "RETURN", 
			"SEMICOLON", "OPEN_PAREN", "CLOSE_PAREN", "OPEN_BRACE", "CLOSE_BRACE", 
			"OPEN_BRACKET", "CLOSE_BRACKET", "ADD", "SUB", "MUL", "DIV", "GREATER_EQUAL", 
			"LESSER_EQUAL", "NOT_EQUAL", "EQUAL", "GREATER_THAN", "LESS_THAN", "ASSIGN", 
			"COMMA", "COMMENT", "WHITESPACES", "INTEGER", "IDENTIFIER"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'&&'", "'||'", "'!'", "'if'", "'else'", "'for'", "'break'", "'true'", 
			"'false'", "'return'", "';'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
			"'+'", "'-'", "'*'", "'/'", "'>='", "'<='", "'!='", "'=='", "'>'", "'<'", 
			"'='", "','"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "AND", "OR", "NOT", "IF", "ELSE", "FOR", "BREAK", "TRUE", "FALSE", 
			"RETURN", "SEMICOLON", "OPEN_PAREN", "CLOSE_PAREN", "OPEN_BRACE", "CLOSE_BRACE", 
			"OPEN_BRACKET", "CLOSE_BRACKET", "ADD", "SUB", "MUL", "DIV", "GREATER_EQUAL", 
			"LESSER_EQUAL", "NOT_EQUAL", "EQUAL", "GREATER_THAN", "LESS_THAN", "ASSIGN", 
			"COMMA", "COMMENT", "WHITESPACES", "INTEGER", "IDENTIFIER"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public CruxLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Crux.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2#\u00be\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\3\2\3\2\3\2\3\3\3\3\3\3\3\4\3\4\3\5\3\5\3\5\3\6\3\6\3\6\3"+
		"\6\3\6\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\n"+
		"\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\r\3"+
		"\r\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3"+
		"\24\3\25\3\25\3\26\3\26\3\27\3\27\3\27\3\30\3\30\3\30\3\31\3\31\3\31\3"+
		"\32\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35\3\36\3\36\3\37\3\37\3\37\3"+
		"\37\7\37\u00a0\n\37\f\37\16\37\u00a3\13\37\3\37\3\37\3 \6 \u00a8\n \r"+
		" \16 \u00a9\3 \3 \3!\3!\3!\7!\u00b1\n!\f!\16!\u00b4\13!\5!\u00b6\n!\3"+
		"\"\3\"\7\"\u00ba\n\"\f\"\16\"\u00bd\13\"\2\2#\3\3\5\4\7\5\t\6\13\7\r\b"+
		"\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26"+
		"+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#\3\2\b\4\2\f\f\17"+
		"\17\5\2\13\f\17\17\"\"\3\2\63;\3\2\62;\4\2C\\c|\6\2\62;C\\aac|\2\u00c2"+
		"\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2"+
		"\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2"+
		"\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2"+
		"\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2"+
		"\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3"+
		"\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\3E\3\2\2\2\5H\3\2\2"+
		"\2\7K\3\2\2\2\tM\3\2\2\2\13P\3\2\2\2\rU\3\2\2\2\17Y\3\2\2\2\21_\3\2\2"+
		"\2\23d\3\2\2\2\25j\3\2\2\2\27q\3\2\2\2\31s\3\2\2\2\33u\3\2\2\2\35w\3\2"+
		"\2\2\37y\3\2\2\2!{\3\2\2\2#}\3\2\2\2%\177\3\2\2\2\'\u0081\3\2\2\2)\u0083"+
		"\3\2\2\2+\u0085\3\2\2\2-\u0087\3\2\2\2/\u008a\3\2\2\2\61\u008d\3\2\2\2"+
		"\63\u0090\3\2\2\2\65\u0093\3\2\2\2\67\u0095\3\2\2\29\u0097\3\2\2\2;\u0099"+
		"\3\2\2\2=\u009b\3\2\2\2?\u00a7\3\2\2\2A\u00b5\3\2\2\2C\u00b7\3\2\2\2E"+
		"F\7(\2\2FG\7(\2\2G\4\3\2\2\2HI\7~\2\2IJ\7~\2\2J\6\3\2\2\2KL\7#\2\2L\b"+
		"\3\2\2\2MN\7k\2\2NO\7h\2\2O\n\3\2\2\2PQ\7g\2\2QR\7n\2\2RS\7u\2\2ST\7g"+
		"\2\2T\f\3\2\2\2UV\7h\2\2VW\7q\2\2WX\7t\2\2X\16\3\2\2\2YZ\7d\2\2Z[\7t\2"+
		"\2[\\\7g\2\2\\]\7c\2\2]^\7m\2\2^\20\3\2\2\2_`\7v\2\2`a\7t\2\2ab\7w\2\2"+
		"bc\7g\2\2c\22\3\2\2\2de\7h\2\2ef\7c\2\2fg\7n\2\2gh\7u\2\2hi\7g\2\2i\24"+
		"\3\2\2\2jk\7t\2\2kl\7g\2\2lm\7v\2\2mn\7w\2\2no\7t\2\2op\7p\2\2p\26\3\2"+
		"\2\2qr\7=\2\2r\30\3\2\2\2st\7*\2\2t\32\3\2\2\2uv\7+\2\2v\34\3\2\2\2wx"+
		"\7}\2\2x\36\3\2\2\2yz\7\177\2\2z \3\2\2\2{|\7]\2\2|\"\3\2\2\2}~\7_\2\2"+
		"~$\3\2\2\2\177\u0080\7-\2\2\u0080&\3\2\2\2\u0081\u0082\7/\2\2\u0082(\3"+
		"\2\2\2\u0083\u0084\7,\2\2\u0084*\3\2\2\2\u0085\u0086\7\61\2\2\u0086,\3"+
		"\2\2\2\u0087\u0088\7@\2\2\u0088\u0089\7?\2\2\u0089.\3\2\2\2\u008a\u008b"+
		"\7>\2\2\u008b\u008c\7?\2\2\u008c\60\3\2\2\2\u008d\u008e\7#\2\2\u008e\u008f"+
		"\7?\2\2\u008f\62\3\2\2\2\u0090\u0091\7?\2\2\u0091\u0092\7?\2\2\u0092\64"+
		"\3\2\2\2\u0093\u0094\7@\2\2\u0094\66\3\2\2\2\u0095\u0096\7>\2\2\u0096"+
		"8\3\2\2\2\u0097\u0098\7?\2\2\u0098:\3\2\2\2\u0099\u009a\7.\2\2\u009a<"+
		"\3\2\2\2\u009b\u009c\7\61\2\2\u009c\u009d\7\61\2\2\u009d\u00a1\3\2\2\2"+
		"\u009e\u00a0\n\2\2\2\u009f\u009e\3\2\2\2\u00a0\u00a3\3\2\2\2\u00a1\u009f"+
		"\3\2\2\2\u00a1\u00a2\3\2\2\2\u00a2\u00a4\3\2\2\2\u00a3\u00a1\3\2\2\2\u00a4"+
		"\u00a5\b\37\2\2\u00a5>\3\2\2\2\u00a6\u00a8\t\3\2\2\u00a7\u00a6\3\2\2\2"+
		"\u00a8\u00a9\3\2\2\2\u00a9\u00a7\3\2\2\2\u00a9\u00aa\3\2\2\2\u00aa\u00ab"+
		"\3\2\2\2\u00ab\u00ac\b \2\2\u00ac@\3\2\2\2\u00ad\u00b6\7\62\2\2\u00ae"+
		"\u00b2\t\4\2\2\u00af\u00b1\t\5\2\2\u00b0\u00af\3\2\2\2\u00b1\u00b4\3\2"+
		"\2\2\u00b2\u00b0\3\2\2\2\u00b2\u00b3\3\2\2\2\u00b3\u00b6\3\2\2\2\u00b4"+
		"\u00b2\3\2\2\2\u00b5\u00ad\3\2\2\2\u00b5\u00ae\3\2\2\2\u00b6B\3\2\2\2"+
		"\u00b7\u00bb\t\6\2\2\u00b8\u00ba\t\7\2\2\u00b9\u00b8\3\2\2\2\u00ba\u00bd"+
		"\3\2\2\2\u00bb\u00b9\3\2\2\2\u00bb\u00bc\3\2\2\2\u00bcD\3\2\2\2\u00bd"+
		"\u00bb\3\2\2\2\b\2\u00a1\u00a9\u00b2\u00b5\u00bb\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}